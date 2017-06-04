#define F_CPU	16000000UL		// MCU Clock Speed - 16MHz
#define BAUDRATE 	57600

#include <avr/io.h>
#include <avr/cpufunc.h>
#include <stdio.h>
#include <avr/interrupt.h>

#include "uart/debugger.h"
#include "timer/timer.h"
#include "adc/adc.h"

float input_buffer[256];


int main(void) 
{
	timer0_set_waveform(TIMER_CTC);
	timer0_enable_clock(64);
	timer0_set_compare_register_A(249);
	timer0_enable_compare_A_interrupt();
	
	dbg_init(BAUDRATE);

	adc_init();

	sei();

	dbg_printf("Initilization finished. \r\n");

	while(2)
	{
		_NOP();
	}
}




uint16_t val = 0;
ISR(TIMER0_COMPA_vect)
{
	val = adc_read();
	dbg_printf("%d\r\n", val);

}


