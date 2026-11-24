#include "telemetry.h"

#include <stdio.h>

int telemetry_to_csv(char *buffer, uint16_t buffer_size,
                     const TelemetryRecord *record)
{
    return snprintf(buffer, buffer_size,
                    "%lu,%d,%d,%d,%d\n",
                    (unsigned long)record->timestamp_ms,
                    record->battery.lipo_voltage_mv,
                    record->battery.life_voltage_mv,
                    record->battery.lipo_current_ma,
                    record->battery.life_current_ma);
}
