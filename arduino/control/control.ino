#include <SPI.h>
#include <PID_v1.h>
/****** parameters *******/
// dac parameters
#define DAC_SS        10
#define DAC_REF       1024
#define DAC_RESOLUTION  4096
 
#define INPUT_PIN   2
 
 
/****** variables ********/
// dac variables
const double min_res = 5600;
const double fourpi = 12.566371;
int j;
int switch_pos;
unsigned int dac_val;
unsigned int readd;
unsigned int readd2;
double pos;
double stepp;
double amp;
double gain;
 
/*** control variables******/
const double dt = 1/2000;
double Kp, Ki, Kd;
double integral, derivative;
double error, previous_error;
double output;
double Setpoint1, Input1, Output1;
double consKp=1, consKi=0.05, consKd=0.25;
 
/*** Call PID******/
PID myPID(&Input1, &Output1, &Setpoint1,consKp,consKi,consKd, DIRECT);
 
/****** main functions ********/
void setup()
{      
  // initialize SPI:
  SPI.begin();
  // initialize dac:
  dac_init();

  Serial.begin(115200);
    
  pinMode(INPUT_PIN, INPUT_PULLUP);
    
  pos = 0;
  j = 0;
  gain = 1;
    
  error = 0;
  output = 0;
 
  //initialize the variables we're linked to
  Input1 = analogRead(A3);
    Kp=analogRead(A0)*5/1024;
Ki=analogRead(A1)*5/1024;
Kd=analogRead(A2)*5/1024;
  Setpoint1 = 512;
 
  //turn the PID on
  myPID.SetMode(AUTOMATIC);
 
 
    
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
    j = 0;
  }
    
  pos += stepp;
  if (pos > fourpi)  pos -= fourpi;
  amp = sin(pos);
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
  //Kp = analogRead(A0)*5;
  //Kp /= 1024;
  Kp=0.5;//analogRead(A0)*5/1024;
Ki=0.5;//analogRead(A1)*5/1024;
Kd=0.1;//analogRead(A2)*5/1024;
 Input1 = analogRead(A3);
 double input2 = Input1*5/1024;
 double setpoint2 = 2.56;
 double error2 = setpoint2 - input2;
  integral= integral+error2*dt;
  double integral2=integral;
  derivative= (error2-previous_error);
  double derivative2=derivative*dt;
  output = Kp*error2+Ki*integral2+Kd*derivative2;
  //output *= 2048/5;
  double output2 = output*2048/5;
  previous_error=error2;
  double output3=output2+80;

  //Serial.println(output3);  
  dac_val = (unsigned int)output2;
  Serial.println(dac_val); 
  dac_write(dac_val);
    
  delayMicroseconds(500);

/*
consKp=analogRead(A0)*5/1024;
consKi=analogRead(A1)*5/1024;
consKd=analogRead(A2)*5/1024;
 Input1 = analogRead(A3);
  myPID.Compute();
  ///analogWrite(3,Output1);
  dac_val = (unsigned int)Output1;
  dac_write(dac_val);  
  delayMicroseconds(500);
  */
  
}
/**********************/

