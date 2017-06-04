#include <avr/io.h>
#include "../timer/timer.h"
#include "mb_control.h"


void mb_control_init(uint8_t duty)
{
	// output pins
	DDRD |= _BV(DDD2) | _BV(DDD3) | _BV(DDD4);
	mb_turn_off();

	// timer
	timer2_set_waveform(TIMER_FAST_PWM);
	timer2_enable_clock(MB_PRESCALER);
	mb_set_duty_cycle(duty);
}

void mb_set_duty_cycle(uint8_t duty)
{
	timer2_set_compare_register_B(duty);
}

void mb_turn_off(void)
{
	timer2_disable_output_B();
	PORTD &= ~_BV(PORTD2) & ~_BV(PORTD4);
}

void mb_turn_left(void)
{
	PORTD &= ~_BV(PORTD4);
	PORTD |= _BV(PORTD2);
	timer2_enable_output_B();
}
void mb_turn_right(void)
{
	PORTD &= ~_BV(PORTD2);
	PORTD |= _BV(PORTD4);
	timer2_enable_output_B();
}