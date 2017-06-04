#define F_CPU	16000000UL		// MCU Clock Speed - 16MHz
#define BAUDRATE 	57600

#include <avr/io.h>
#include <avr/cpufunc.h>
#include <stdio.h>
#include <string.h>
#include <avr/interrupt.h>

#include "uart/debugger.h"
#include "timer/timer.h"
#include "adc/adc.h"
#include "dft/dft.h"

#define FFT_SIZE	FFT_LEN

double input_buffer[256];
double data_buffer[FFT_SIZE];
double real_buffer[FFT_SIZE];
double imag_buffer[FFT_SIZE];
double output_buffer[FFT_SIZE];

uint8_t n = 0;

int main(void) 
{
	timer0_set_waveform(TIMER_CTC);
	timer0_enable_clock(256);
	timer0_set_compare_register_A(249);	// 250 Hz
	timer0_enable_compare_A_interrupt();
	
	dbg_init(BAUDRATE);

	adc_init();

	sei();

	dbg_printf("Initilization finished. \r\n");

	while(2)
	{
		if (n >= FFT_SIZE)
		{
			uint8_t i;
			cli();
			memcpy(data_buffer, input_buffer, FFT_SIZE * sizeof(double)); 
			/*
			for (i = 0; i < FFT_SIZE; i++)
			{
				data_buffer[i] = 0.0;
				data_buffer[i] = 1.0;
				//data_buffer[i] = input_buffer[i];
			}*/
			
			// fft
			dft(data_buffer, real_buffer, imag_buffer, FFT_SIZE);

			dbg_printf("f:");
			for (i = 0; i < FFT_SIZE - 1; i++)
			{
				output_buffer[i] = real_buffer[i]*real_buffer[i] + imag_buffer[i]*imag_buffer[i];
				dbg_printf("%.2f,", output_buffer[i]);
				//dbg_printf("%.2f,", data_buffer[i]);
			}
			output_buffer[i] = real_buffer[i]*real_buffer[i] + imag_buffer[i]*imag_buffer[i];
			dbg_printf("%.2f\r\n", output_buffer[i]);
			//dbg_printf("%.2f\r\n", data_buffer[i]);
			n = 0;
			sei();

		}
		_NOP();
	}
}




uint16_t val = 0;
double fval = 0.0;
ISR(TIMER0_COMPA_vect)
{
	val = adc_read();
	fval = (double)val / 1024 * 5 - 2.5;
	if (n < FFT_SIZE)	input_buffer[n++] = fval;
	//dbg_printf("d:%.2f\r\n", fval);
}


