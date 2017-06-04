#include <avr/io.h>
#include "../timer/timer.h"
#include "servo.h"

static uint16_t servo_pos;

static uint16_t servo_set_pos(uint16_t pos)
{
	if (pos < SERVO_POS_MIN)
	{
		timer1_set_compare_register_A(SERVO_POS_MIN);
		servo_pos = SERVO_POS_MIN;
	}
	else if (pos > SERVO_POS_MAX)
	{
		timer1_set_compare_register_A(SERVO_POS_MAX);
		servo_pos = SERVO_POS_MAX;
	}
	else
	{
		timer1_set_compare_register_A(pos);
		servo_pos = pos;
	}
	return (servo_pos - SERVO_POS_MIN)/SERVO_STEP;
}

void servo_init()
{
	// output pins
	DDRB |= _BV(DDB1);

	// timer
	timer1_set_icr(SERVO_TIMER_MAX);
	timer1_set_waveform(TIMER_CTC_FAST_PWM);
	servo_set_pos(SERVO_CENTER);
	timer1_enable_clock(SERVO_PRESCALER);
	timer1_enable_output_A();
}

uint16_t servo_clkwise(uint16_t steps)
{
	return servo_set_pos(servo_pos + steps * SERVO_STEP);
}

uint16_t servo_cclkwise(uint16_t steps)
{
	return servo_set_pos(servo_pos - steps * SERVO_STEP);
}

uint16_t servo_goto(uint16_t pos)
{
	return servo_set_pos(pos * SERVO_STEP + SERVO_POS_MIN);
}