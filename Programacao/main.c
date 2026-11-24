#include <stdint.h>
#include "adc_reader.h"
#include "sensoriamento.h"
#include "telemetry.h"

#ifndef HOST_BUILD
#include "ch32v003fun.h"
#endif

/* Provisional hardware configuration:
 * Assumption: 20-pin CH32V003 variant.
 * PA1/A1: not used
 * PA2/A0: not used
 * PD2/A3: LiPo voltage
 * PD3/A4: LiPo current
 * PD4/A7: LiFe voltage
 * PD6/A6: LiFe current
 * PC5/SCK, PC6/MOSI, PC7/MISO, PC1/NSS: SPI MicroSD
 * VDD: regulated 3.3 V, VSS: ground
 */
#define LIPO_VOLTAGE_PIN 3
#define LIFE_VOLTAGE_PIN 7
#define LIPO_CURRENT_PIN 4
#define LIFE_CURRENT_PIN 6

#define ADC_REFERENCE_MV 3300
#define VOLTAGE_TOP_OHMS 10000
#define VOLTAGE_BOTTOM_OHMS 10000
#define CURRENT_ZERO_MV 1650
#define ACS758_SENSITIVITY_MA_PER_V 25000

static uint16_t platform_read_adc(uint8_t channel)
{
#ifdef HOST_BUILD
    (void)channel;
    return 512;
#else
    (void)channel;
    return 512;
#endif
}

static uint32_t platform_millis(void)
{
#ifdef HOST_BUILD
    static uint32_t now_ms;
    now_ms += 10;
    return now_ms;
#else
    return 0;
#endif
}

static void platform_spi_sd_append(const char *line)
{
    (void)line;
}

int main(void)
{
    uint32_t next_log_ms = ADC_LOG_INTERVAL_MS;
    char line[96];

#ifndef HOST_BUILD
    SystemInit();
#endif

    for (;;) {
        uint32_t now_ms = platform_millis();

        BatterySample sample;
        sample.lipo_voltage_mv = adc_voltage_to_mv(
            platform_read_adc(LIPO_VOLTAGE_PIN), ADC_REFERENCE_MV,
            VOLTAGE_TOP_OHMS, VOLTAGE_BOTTOM_OHMS);
        sample.life_voltage_mv = adc_voltage_to_mv(
            platform_read_adc(LIFE_VOLTAGE_PIN), ADC_REFERENCE_MV,
            VOLTAGE_TOP_OHMS, VOLTAGE_BOTTOM_OHMS);
        sample.lipo_current_ma = adc_current_to_ma(
            platform_read_adc(LIPO_CURRENT_PIN), ADC_REFERENCE_MV,
            CURRENT_ZERO_MV, ACS758_SENSITIVITY_MA_PER_V);
        sample.life_current_ma = adc_current_to_ma(
            platform_read_adc(LIFE_CURRENT_PIN), ADC_REFERENCE_MV,
            CURRENT_ZERO_MV, ACS758_SENSITIVITY_MA_PER_V);

        if (now_ms >= next_log_ms) {
            TelemetryRecord record = {now_ms, sample};
            if (telemetry_to_csv(line, sizeof(line), &record) > 0) {
                platform_spi_sd_append(line);
            }
            next_log_ms += ADC_LOG_INTERVAL_MS;
        }
    }

    return 0;
}
