#ifndef ADC_READER_H
#define ADC_READER_H

#include <stdint.h>

#define ADC_MAX_COUNTS 1023

uint16_t adc_raw_to_mv(uint16_t raw, uint16_t reference_mv);
uint16_t adc_voltage_to_mv(uint16_t raw, uint16_t reference_mv,
                           uint16_t r_top_ohms, uint16_t r_bottom_ohms);
int16_t adc_current_to_ma(uint16_t raw, uint16_t reference_mv,
                          uint16_t zero_mv, int32_t sensitivity_ma_per_v);

#endif
