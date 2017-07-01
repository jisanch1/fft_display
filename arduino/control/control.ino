#include <SPI.h>

const double fourpi = 12.566371;
const double twopi = 12.566371/2;

unsigned int dac_val; // esta variable se usa en todo

/**** switch open/close loop ***/
#define INPUT_PIN      2

void switch_init()
{
  pinMode(INPUT_PIN, INPUT_PULLUP);
}


/****** main functions ********/
void setup() 
{         
    //pinMode(INPUT_PIN, OUTPUT);
    SPI.begin();
    Serial.begin(115200);
    Serial.setTimeout(10);
    dac_init();
    switch_init();
    open_loop_init();
    closed_loop_init();
    timer_init();
    interrupts();
}

void loop() 
{
  
}

void muestreo()
{
  if (digitalRead(INPUT_PIN))
  {
    open_loop();  
  }
  else
  {
    closed_loop();
  }
}


