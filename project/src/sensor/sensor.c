#include <avr/io.h>
#include <avr/interrupt.h>
#include "../timer/timer.h"
#include "sensor.h"

static enum sensor_stage st;
static uint16_t count;

void sensor_init()
{
	// comm pins
	DDRD |= _BV(SENSOR_TRIG_PIN); //trig
	DDRD &= ~_BV(SENSOR_ECHO_PIN);	//echo
	PORTD &= ~_BV(SENSOR_TRIG_PIN);
	PORTD |= _BV(SENSOR_ECHO_PIN);

	// timer
	timer2_set_waveform(TIMER_CTC);
	timer2_set_compare_register_A(SENSOR_TIMER_MAX);
	timer2_enable_compare_A_interrupt();

	// external interrupt, any change generate interrupt
	EICRA |= _BV(ISC00);
	EICRA &= ~_BV(ISC01);

	//idle
	st = SENSOR_IDLE;
	count = 0;
}

static inline void sensor_enable_echo()
{
	EIMSK |= _BV(INT0);
}

static inline void sensor_disable_echo()
{
	EIMSK &= ~_BV(INT0);
}

static void sensor_send_request()
{
	PORTD |= _BV(SENSOR_TRIG_PIN);
	st = SENSOR_SENDING_REQUEST;
	timer2_reset();
	timer2_enable_clock(SENSOR_PRESCALER);
}

void sensor_detect()
{
	count = 0;
	sensor_send_request();
}

uint16_t sensor_read_value()
{
	return count*34/200; 
}

enum sensor_stage sensor_get_stage()
{
	return st;
}

ISR(TIMER2_COMPA_vect)
{
	switch (st)
	{
		case SENSOR_SENDING_REQUEST:
			PORTD &= ~_BV(SENSOR_TRIG_PIN);
			timer2_disable_clock();
			sensor_enable_echo();
			st = SENSOR_WAITING_RESPONSE;
			break;
		case SENSOR_MEASURING:
			count++;
			break;
		default:
			break;
	}
}	

ISR(INT0_vect) 
{
	switch (st)
	{
		case SENSOR_WAITING_RESPONSE:
			st = SENSOR_MEASURING;
			timer2_reset();
			timer2_enable_clock(SENSOR_PRESCALER);
			break;
		case SENSOR_MEASURING:
			timer2_disable_clock();
			sensor_disable_echo();
			st = SENSOR_IDLE;
			break;
		default:
			break;
	}
}