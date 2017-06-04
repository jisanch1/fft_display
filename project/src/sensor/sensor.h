#ifndef _SENSOR_H_
#define _SENSOR_H_

#define SENSOR_PRESCALER	1
#define SENSOR_TIMER_MAX	159
#define SENSOR_TRIG_PIN		PORTD3
#define SENSOR_ECHO_PIN		PORTD4
#define SENSOR_COUNT_MAX	5000


enum sensor_stage 
{
	SENSOR_IDLE,
	SENSOR_SENDING_REQUEST,
	SENSOR_WAITING_RESPONSE,
	SENSOR_MEASURING,
	SENSOR_FINISHED
};

void sensor_init();
void sensor_detect();
uint16_t sensor_read_value();
enum sensor_stage sensor_get_stage();

#endif // _SENSOR_H_