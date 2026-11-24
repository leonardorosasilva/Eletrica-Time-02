#include "adc_reader.h"

uint16_t adc_raw_to_mv(uint16_t raw, uint16_t reference_mv)
{
    if (raw > ADC_MAX_COUNTS) {
        raw = ADC_MAX_COUNTS;
    }
    return (uint16_t)(((uint32_t)raw * reference_mv) / ADC_MAX_COUNTS);
}

uint16_t adc_voltage_to_mv(uint16_t raw, uint16_t reference_mv,
                           uint16_t r_top_ohms, uint16_t r_bottom_ohms)
{
    uint32_t adc_mv = adc_raw_to_mv(raw, reference_mv);
    uint32_t divider_total = (uint32_t)r_top_ohms + r_bottom_ohms;
    if (divider_total == 0) {
        return 0;
    }
    return (uint16_t)((adc_mv * divider_total) / r_bottom_ohms);
}

int16_t adc_current_to_ma(uint16_t raw, uint16_t reference_mv,
                          uint16_t zero_mv, int32_t sensitivity_ma_per_v)
{
    int32_t adc_mv = adc_raw_to_mv(raw, reference_mv);
    int32_t delta_ma = ((adc_mv - (int32_t)zero_mv) *
                        sensitivity_ma_per_v) / 1000;

    return (int16_t)delta_ma;
}
