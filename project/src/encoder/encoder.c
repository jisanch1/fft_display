#include <avr/io.h>
#include "encoder.h"


void encoder_init(void)
{
	DDRC &= ~_BV(DDC0);
	PORTC |= _BV(PORTC0);
}

enc_pos encoder_read(void)
{
	if (PINC & _BV(PINC0))
	{
		return ENC_DOWN;
	}
	else
	{
		return ENC_UP;
	}
}

int enc_angle(int state)
{
	return state * 90 / 50 + 90;
}