#define F_CPU	16000000UL		// MCU Clock Speed - 16MHz
#define BAUDRATE 	57600

#include <avr/io.h>
#include <stdio.h>
#include <avr/interrupt.h>

#include "uart/debugger.h"


int main(void)
{

	dbg_init(BAUDRATE);

	sei();

	dbg_printf("Initilization finished. \r\n");

	while(2);
}






ISR(TIMER0_COMPA_vect)
{

}

ISR(PCINT1_vect)
{

}
