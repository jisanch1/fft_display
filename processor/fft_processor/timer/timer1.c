#include <avr/io.h>
#include <avr/interrupt.h>
#include "timer.h"

/*void timer2_set_waveform(waveform_mode_te wf)
{
	switch(wf)
	{
	case TIMER_NORMAL:
		TCCR2A &= ~_BV(WGM20) & ~_BV(WGM21);
		TCCR2B &= ~_BV(WGM22);
		break;
	case TIMER_CTC:
		TCCR2A &= ~_BV(WGM20);
		TCCR2A |= _BV(WGM21);
		TCCR2B &= ~_BV(WGM22);
		break;
	case TIMER_FAST_PWM:
		TCCR2A |= _BV(WGM21) | _BV(WGM20);
		TCCR2B &= ~_BV(WGM22);
		break;		
	case TIMER_PHC_PWM:
		TCCR2A &= ~_BV(WGM21);
		TCCR2A |= _BV(WGM20);
		TCCR2B &= ~_BV(WGM22);
		break;
	case TIMER_CTC_FAST_PWM:
		TCCR2A &= ~_BV(WGM21);
		TCCR2A |= _BV(WGM20);
		TCCR2B |= _BV(WGM22);
		break;
	case TIMER_CTC_PHC_PWM:
		TCCR2A |= _BV(WGM21) | _BV(WGM20);
		TCCR2B |= _BV(WGM22);
		break;
	default:
		break;
	}
}
*/

// temporal
void timer1_set_waveform(waveform_mode_te wf)
{
	switch(wf)
	{
	case TIMER_CTC_FAST_PWM:
		TCCR1A |= _BV(WGM11);
		TCCR1A &= ~_BV(WGM10);
		TCCR1B |= _BV(WGM13) | _BV(WGM12);
	default:
		break;
	}
	
}

/* Clock and prescaler */
uint8_t timer1_enable_clock(uint16_t prescaler)
{
	switch (prescaler)
	{
	case 1:
		TCCR1B &= ~_BV(CS12) & ~_BV(CS11);
		TCCR1B |= _BV(CS10);
		break;
	case 8:
		TCCR1B &= ~_BV(CS12) & ~_BV(CS10);
		TCCR1B |= _BV(CS11);
		break;
	case 64:
		TCCR1B &= ~_BV(CS12);
		TCCR1B |= _BV(CS11) | _BV(CS10);
		break;
	case 256:
		TCCR1B &= ~_BV(CS11) & ~_BV(CS10);
		TCCR1B |= _BV(CS12);
		break;
	case 1024:
		TCCR1B &= ~_BV(CS11);
		TCCR1B |= _BV(CS12) | _BV(CS10);
		break;
	default:
		timer1_disable_clock();
		return TIMER_BAD_CLOCK_SET;
		break;
	}
	return TIMER_OK;
}

inline void timer1_disable_clock(void)
{
	TCCR1B &= ~_BV(CS12) & ~_BV(CS11) & ~_BV(CS10);
}


/* Configure compare registers */
void timer1_set_compare_register_A(uint16_t value)
{
	OCR1A = value;
	//OCR1AL = (uint8_t)value;
	//OCR1AH = (uint8_t)(value >> 8);
}

void timer1_set_compare_register_B(uint16_t value)
{
	OCR1B = value;
	//OCR1BL = (uint8_t)value;
	//OCR1BH = (uint8_t)(value >> 8);
}

void timer1_set_icr(uint16_t value)
{
	ICR1 = value;
}

/* Interrupts */
inline void timer1_enable_compare_A_interrupt(void)
{
	TIMSK1 |= _BV(OCIE1A);
} 

inline void timer1_disable_compare_A_interrupt(void)
{
	TIMSK1 &= ~_BV(OCIE1A);
} 

inline void timer1_enable_compare_B_interrupt(void)
{
	TIMSK1 |= _BV(OCIE1B);
} 

inline void timer1_disable_compare_B_interrupt(void)
{
	TIMSK1 &= ~_BV(OCIE1B);
} 

inline void timer1_enable_overflow_interrupt(void)
{
	TIMSK1 |= _BV(TOIE1);
} 

inline void timer1_disable_overflow_interrupt(void)
{
	TIMSK1 &= ~_BV(TOIE1);
} 





// temporales
void timer1_enable_output_A(void)
{
	DDRB |= _BV(DDB1);
	TCCR1A |= _BV(COM1A1);
	TCCR1A &= ~_BV(COM1A0);
}

void timer1_disable_output_A(void)
{
	TCCR1A &= ~_BV(COM1A1);
	TCCR1A &= ~_BV(COM1A0);
	PORTB &= ~_BV(PORTB1);
}