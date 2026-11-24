#ifndef TELEMETRY_H
#define TELEMETRY_H

#include <stdint.h>
#include "sensoriamento.h"

typedef struct {
    uint32_t timestamp_ms;
    BatterySample battery;
} TelemetryRecord;

int telemetry_to_csv(char *buffer, uint16_t buffer_size,
                     const TelemetryRecord *record);

#endif
