#include <SPI.h>

/****** parameters *******/
// dac parameters
#define DAC_SS          10
#define DAC_REF         1024
#define DAC_RESOLUTION  4096

#define INPUT_PIN      2

/****** variables ********/
// dac variables 
const double min_res = 5600;
const double fourpi = 12.566371;
const double twopi = fourpi/2;
int j;
int switch_pos;
unsigned int dac_val;
unsigned int readd;
unsigned int readd2;
double pos;
double stepp;
double amp;
double gain;
double phase;

/*** control variables******/
const double dt = 1/2000;
double Kp, Ki, Kd;
double integral, derivative;
double error, previous_error;
double output;


/****** main functions ********/
void setup() 
{         
    // initialize SPI:
    SPI.begin();
    // initialize dac:
    dac_init();
    
    pinMode(INPUT_PIN, INPUT_PULLUP);
    
    pos = 0;
    j = 0;
    gain = 1;
    
    error = 0;
    output = 0;
    
}

void loop() 
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

/*** dac functions ***/
void dac_init()
{
    // set the dac pin as an output:
    pinMode(DAC_SS, OUTPUT);
    // start the dac at zero
    dac_val = 0;
}

void dac_write(unsigned int val) 
{
    // valid dac values
    val = constrain(val, 0, DAC_RESOLUTION - 1);
    // mapping to resolution of dac
    
    val += 0x3000;
    
    // transmision to dac
    digitalWrite(DAC_SS, LOW);
    SPI.transfer(val>>8);
    SPI.transfer(val);
    digitalWrite(DAC_SS, HIGH);
}

void open_loop()
{
  if (j%100 == 0)
    {
      readd = analogRead(A0);
      stepp = (double)readd / min_res;
      readd2 = analogRead(A1);
      gain = (double)readd2; 
      gain /= 1024;
      phase = analogRead(A2);
      phase /= 512;
      phase -= 1;
      phase *= twopi;
      j = 0;
    }
    
    pos += stepp;
    if (pos > fourpi)  pos -= fourpi;
    amp = sin(pos + phase);
    amp *= gain;
    amp += 1;
    amp *= 2048;
    
    dac_val = (unsigned int)amp;
    dac_write(dac_val);

    delayMicroseconds(100);
    j++;
}

void closed_loop()
{
    error = analogRead(A3)*5/1024 - 2.5;
    Kp = analogRead(A1)*5;
    Kp /= 1024;
    output = Kp * error;
    output *= 2048/5;
    
    dac_val = (unsigned int)output;
    dac_write(dac_val);
    
    delayMicroseconds(500);
}
/**********************/
