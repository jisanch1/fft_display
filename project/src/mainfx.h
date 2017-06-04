#define MAIN_PRESCALER	64
#define TIMER_MAX	249
#define BAUDRATE 	57600
#define DUTY_CYCLE	0x7F
#define SAMPLE_PERIOD	300
#define MEDIAN_SAMPLES	9
#define THRESHOLD_GAP	5
void next(void);
uint8_t calc(void);
void shoot(void);
void mabort(void);