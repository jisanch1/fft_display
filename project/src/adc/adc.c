#include <avr/io.h> 
#include <avr/cpufunc.h>
#include "adc.h"
#define ADC_IS_WORKING  ADCSRA & (1 << ADSC)

void adc_init(void)
{
    ADCSRA |= _BV(ADPS2) | _BV(ADPS1) | _BV(ADPS0);                        // ADC prescaler ser to clk/128 (125 kHz).
    ADMUX |= _BV(REFS0);                        // AREF at VREF.
    ADCSRA |= _BV(ADEN);                        // Enable ADC.

    adc_select(0);   							// ADC0 as input. (PC0)
}

void adc_select(uint8_t ax)
{
    ADMUX |= ax & 0x07;                               
}

uint16_t adc_read(void)
{
    ADCSRA |= _BV(ADSC);                        // Strat adc conversion

    while(ADC_IS_WORKING){_NOP();}

    uint16_t ret = ADCL;
    ret += ADCH << 8;
    return ret;                                // Read most significative pins.
}