#include <assert.h>
#include <stdio.h>
#include "adc_reader.h"
#include "sensoriamento.h"
#include "telemetry.h"

int main(void)
{
    assert(adc_raw_to_mv(0, 3300) == 0);
    assert(adc_raw_to_mv(512, 3300) == 1651);
    assert(adc_raw_to_mv(1023, 3300) == 3300);
    assert(adc_voltage_to_mv(512, 3300, 10000, 10000) == 3302);
    assert(adc_current_to_ma(512, 3300, 1650, 25000) == 0);

    TelemetryRecord record = {
        1000,
        {8400, 7200, 1250, -250}
    };
    char line[96];
    int size = telemetry_to_csv(line, sizeof(line), &record);

    assert(size > 0);
    assert(line[0] != '\0');
    printf("mock OK: %s", line);
    return 0;
}
