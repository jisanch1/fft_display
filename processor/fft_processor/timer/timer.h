#ifndef _TIMER_H_
#define _TIMER_H_

typedef enum {	
	TIMER_NORMAL, 
	TIMER_CTC, 
	TIMER_FAST_PWM, 
	TIMER_PHC_PWM,
	TIMER_CTC_FAST_PWM, 
	TIMER_CTC_PHC_PWM
} waveform_mode_te;

typedef enum {
	TIMER_OK, 
	TIMER_BAD_CLOCK_SET
} timer_error_handler_te;

///////// Timer 0 /////////////
void timer0_set_waveform(waveform_mode_te wf);
/* Clock and prescaler */
uint8_t timer0_enable_clock(uint16_t prescaler);
void timer0_disable_clock(void);
/* Configure compare registers */
void timer0_set_compare_register_A(uint8_t value);
void timer0_set_compare_register_B(uint8_t value);
/* Interrupts */
void timer0_enable_compare_A_interrupt(void);
void timer0_disable_compare_A_interrupt(void);
void timer0_enable_compare_B_interrupt(void);
void timer0_disable_compare_B_interrupt(void);
void timer0_enable_overflow_interrupt(void);
void timer0_disable_overflow_interrupt(void);



///////// Timer 2 /////////////
void timer2_reset(void);
void timer2_set_waveform(waveform_mode_te wf);
/* Clock and prescaler */
uint8_t timer2_enable_clock(uint16_t prescaler);
void timer2_disable_clock(void);
/* Configure compare registers */
void timer2_set_compare_register_A(uint8_t value);
void timer2_set_compare_register_B(uint8_t value);
/* Interrupts */
void timer2_enable_compare_A_interrupt(void);
void timer2_disable_compare_A_interrupt(void);
void timer2_enable_compare_B_interrupt(void);
void timer2_disable_compare_B_interrupt(void);
void timer2_enable_overflow_interrupt(void);
void timer2_disable_overflow_interrupt(void);
// temporales
void timer2_enable_output_B(void);
void timer2_disable_output_B(void);

///////// Timer 1 /////////////
void timer1_set_waveform(waveform_mode_te wf);
/* Clock and prescaler */
uint8_t timer1_enable_clock(uint16_t prescaler);
void timer1_disable_clock(void);
/* Configure compare registers */
void timer1_set_compare_register_A(uint16_t value);
void timer1_set_compare_register_B(uint16_t value);
void timer1_set_icr(uint16_t value);
/* Interrupts */
void timer1_enable_compare_A_interrupt(void);
void timer1_disable_compare_A_interrupt(void);
void timer1_enable_compare_B_interrupt(void);
void timer1_disable_compare_B_interrupt(void);
void timer1_enable_overflow_interrupt(void);
void timer1_disable_overflow_interrupt(void);
// temporales
void timer1_enable_output_A(void);
void timer1_disable_output_A(void);

#endif // _TIMER_H_