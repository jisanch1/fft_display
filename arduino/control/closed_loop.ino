/*** closed loop ******/
#define KP_MAX  10
#define SAMPLE_FREQ   2000

const double dt = 1/SAMPLE_FREQ;
double Kp, Ki, Kd;
double integral, derivative;
double error, previous_error;
double output;
double Setpoint1, Input1, Output1;
double consKp=1, consKi=0.05, consKd=0.25;

void closed_loop_init()
{
    error = 0;
    output = 0;
}

void closed_loop()
{
  //Kp = analogRead(A0)*5;
  //Kp /= 1024;
  Kp=0.3;//analogRead(A0)*5/1024;
  Ki=1;//analogRead(A1)*5/1024;
  Kd=0.06;//analogRead(A2)*5/1024;
  Input1 = analogRead(A3);
  double input2 = Input1*5/1024;
  double setpoint2 = 2.56;
  double error2 = setpoint2 - input2;
  error2 = filter(error2);
  error2 = integrator(error2);
  integral= integral+error2*dt;
  double integral2=integral;
  derivative= (error2-previous_error);
  double derivative2=derivative*dt;
  output = Kp*error2+Ki*integral2+Kd*derivative2;
  double output2pre = output+2.5;
  double output3pre = -output+2.5;
  double output2 = output2pre*4096/5;
  double output3 = output3pre*4096/5;
  previous_error=error2;

  if(output3<=0)
  {
  output3=0;
  
  }

    if(output3>=4095)
  {
  output3=4095;
  
  }

   if(output2<=0)
  {
  output2=0;
  
  }

    if(output2>=4095)
  {
  output2=4095;
  
  }
  
  dac_val = (unsigned int)output2;

  //Serial.println(output2);  
  //Serial.println(dac_val); 
  dac_write(dac_val);
    

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
