#ifndef _MB_CONTROL_H_
#define _MB_CONTROL_H_

#define MB_PRESCALER	64

typedef enum 
{
	MB_OFF,
	MB_LEFT,
	MB_RIGHT
} mb_state;

void mb_control_init(uint8_t duty);
void mb_set_duty_cycle(uint8_t duty);
void mb_turn_off(void);
void mb_turn_left(void);
void mb_turn_right(void);

#endif // _MB_CONTROL_H_