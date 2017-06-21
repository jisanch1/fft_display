#include <SPI.h>

/****** DAC *******/
#define DAC_SS          10
#define DAC_REF         1024
#define DAC_RESOLUTION  4096

unsigned int dac_val; // esta variable se usa en todo

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

/****** FILTER ******/
#define FILTER_LEN  20

double filter_buf[FILTER_LEN];

// 100 Hz
const double coefs [FILTER_LEN] = {
  -0.000370650405764,
   0.002994542610923,
   0.007160485655445,
   0.003631939576628,
  -0.016763863367532,
  -0.040164611082293,
  -0.024537039674789,
   0.063356947992872,
   0.199860056559447,
   0.304832192135062,
   0.304832192135062,
   0.199860056559447,
   0.063356947992872,
  -0.024537039674789,
  -0.040164611082293,
  -0.016763863367532,
   0.003631939576628,
   0.007160485655445,
   0.002994542610923,
  -0.000370650405764,
};

double filter(double new_val)
{
  
  // se despazan los valores en 1
  int i;
  for (i = FILTER_LEN - 1; i > 0; i--)
  {
    filter_buf[i] = filter_buf[i-1];
  }

  // se asigna el nuevo valor
  filter_buf[0] = new_val;

  //se calcula el valor de salida
  double ret = 0;
  for (i = 0; i < FILTER_LEN; i++)
  {
    ret += coefs[i] * filter_buf[i];
  }

  return ret;
}

/**** switch open/close loop ***/
#define INPUT_PIN      2

void switch_init()
{
  pinMode(INPUT_PIN, INPUT_PULLUP);
}

/****** open loop ********/
// dac variables 
const double min_res = 5600;
const double fourpi = 12.566371;
const double twopi = 12.566371/2;
int check;
int switch_pos;

double pos;
double stepp;
double amp;
double gain;
double phase;

void open_loop_init()
{
    pos = 0;
    check = 0;
    gain = 1;
}

void open_loop()
{
  if (check % 100 == 0)
    {
      stepp = analogRead(A0);
      stepp /= min_res;
      gain = analogRead(A1);
      gain /= 1024;
      phase = analogRead(A2);
      phase /= 512;
      phase -= 1;
      phase *= twopi;
      check = 0;
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
    check++;
}

/*** closed loop ******/
#define KP_MAX  10
#define SAMPLE_FREQ   2000

const double dt = 1/SAMPLE_FREQ;
double Kp, Ki, Kd;
double integral, derivative;
double error, previous_error;
double output;

void closed_loop_init()
{
    error = 0;
    output = 0;
}

void closed_loop()
{
    error = analogRead(A3);
    error = error*5/1024 - 2.5;
    error = filter(error);
    Kp = analogRead(A1)*KP_MAX;
    Kp /= 1024;
    output = Kp * (0 - error);
    output += 2.5;
    output /= 5;
    output *= 4096;
    
    dac_val = (unsigned int)output;
    dac_write(dac_val);
    
    delayMicroseconds(1000000/SAMPLE_FREQ);
}

/****** main functions ********/
void setup() 
{         
    SPI.begin();
    dac_init();
    switch_init();
    open_loop_init();
    closed_loop_init();
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


