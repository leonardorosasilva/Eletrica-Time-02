#ifndef SENSORIAMENTO_H
#define SENSORIAMENTO_H

#include <stdint.h>

#define ADC_SAMPLE_HZ 100
#define LOG_HZ 10
#define ADC_LOG_INTERVAL_MS (1000 / LOG_HZ)

typedef enum {
    SENSOR_TYPE_TEMPERATURE,
    SENSOR_TYPE_HUMIDITY,
    SENSOR_TYPE_PRESSURE,
    SENSOR_TYPE_LIGHT,
    SENSOR_TYPE_MOTION,
    SENSOR_TYPE_SOUND,
    SENSOR_TYPE_PROXIMITY,
    SENSOR_TYPE_GAS,
    SENSOR_TYPE_ACCELEROMETER,
    SENSOR_TYPE_GYROSCOPE,
    SENSOR_TYPE_MAGNETOMETER,
    SENSOR_TYPE_BATTERY_VOLTAGE,
    SENSOR_TYPE_BATTERY_CURRENT
} SensorType;

typedef struct {
    int16_t lipo_voltage_mv;
    int16_t life_voltage_mv;
    int16_t lipo_current_ma;
    int16_t life_current_ma;
} BatterySample;

#endif
