/*** closed loop ******/
#define SAMPLE_FREQ 2500
enum { UP, DOWN};

double measured, output;
double count, paso, fase, freq;
int st, last;

void closed_loop_init()
{
  measured = 0;
  last = 0;
  fase = twopi/10;
}

void closed_loop()
{
  measured = toVolt(analogRead(A3));  // entre -2.5 y 2.5
  st = (measured > 0) ? UP : DOWN;
  if (st == UP && last == DOWN)
  {
    reset();
  }
  output = sin(paso*count + fase);

  dac_val = toDac(output);
  dac_write(dac_val);
  
  last = st;
  count++;
}

void reset()
{
  paso = twopi/count;
  freq = SAMPLE_FREQ/count;
  count = 0;
}

double toVolt(int adcval)
{
  double ret = (double)adcval;
  ret /= 1024;
  ret *= 5;
  ret -= 2.5;
  return ret;
}

unsigned int toDac(double volt)
{
  volt += 2.5;
  volt /= 5;
  volt *= 4096;
  return (unsigned int) volt;
}

double Kp, Ki, Kd;

#if 0

const double dt = 0.001;
const double setpoint = 0;
double measured;
double Kp, Ki, Kd;
double integral, derivative;
double error, previous_error;
double output;

double distancia;

void closed_loop_init()
{
    error = 0;
    output = 0;
    integral = 0;
    previous_error = 0;
    Kp = 2;
    Ki = 0;
    Kd = 0.005;
}

void closed_loop()
{
  measured = toVolt(analogRead(A3));  // entre -2.5 y 2.5
  measured = 2*expfilter(measured);
  
  measured = distance(100000*measured, distancia, dt);
  distancia = measured;
  
  error = setpoint - measured;
  integral = integral + error*dt;
  derivative = (error - previous_error)/dt;
  output = Kp*error + Ki*integral + Kd*derivative;
  //output = Kp*error + Kd*derivative;
  previous_error = error;

  dac_val = toDac(output);
  dac_write(dac_val);
  
  //Serial.println(output);
  //Serial.print('<');
  //Serial.print(measured);
  //Serial.print(',');
  //Serial.print(output);
  //Serial.println('>');
}
#endif
