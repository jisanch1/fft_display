#include <SPI.h>

/****** parameters *******/
// dac parameters
#define DAC_SS          10
#define DAC_REF         1024
#define DAC_RESOLUTION  4096

/****** variables ********/
// dac variables 
const double min_res = 5800;
const double fourpi = 12.566371;
int j;
unsigned int dac_val;
unsigned int readd;
double pos;
double stepp;
double amp;


/****** main functions ********/
void setup() 
{         
    // initialize SPI:
    SPI.begin();
    // initialize dac:
    dac_init();
    
    pos = 0;
    j = 0;
}

void loop() 
{
    if (j%100 == 0)
    {
      readd = analogRead(A1);
      stepp = (double)readd / min_res;
    }
    pos += stepp;
    if (pos > fourpi)  pos -= fourpi;
    amp = sin(pos);
    amp += 1;
    amp *= 2048;
    dac_val = (unsigned int)amp;

    dac_write(dac_val);

    delayMicroseconds(100);
    j++;
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
/**********************/
