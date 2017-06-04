#ifndef _SERVO_H_
#define _SERVO_H_

// valores delicados (dependientes entre ellos)
#define SERVO_PRESCALER	64
#define SERVO_TIMER_MAX	4999
#define SERVO_STEP		3
#define SERVO_POS_MIN	150
#define SERVO_POS_MAX	600
#define SERVO_CENTER	375
#define SERVO_NUM_POS	151

void servo_init();
uint16_t servo_clkwise(uint16_t steps);
uint16_t servo_cclkwise(uint16_t steps);
uint16_t servo_goto(uint16_t pos);


#endif // _SERVO_H_