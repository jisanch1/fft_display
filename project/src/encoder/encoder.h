#ifndef _ENCODER_H_
#define _ENCODER_H_

typedef enum 
{
	ENC_DOWN,
	ENC_UP
} enc_pos;

void encoder_init(void);
enc_pos encoder_read(void);
int enc_angle(int state);

#endif // _ENCODER_H_