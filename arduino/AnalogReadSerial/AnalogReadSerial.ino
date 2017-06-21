
/****** FILTER ******/
#define FILTER_LEN  20

double sensorValue;
double filter_buf[FILTER_LEN];
double coefs [FILTER_LEN] = {
   -0.0003,
   -0.0035,
    0.0059,
    0.0037,
   -0.0245,
    0.0211,
    0.0387,
   -0.1059,
    0.0361,
    0.5287,
    0.5287,
    0.0361,
   -0.1059,
    0.0387,
    0.0211,
   -0.0245,
    0.0037,
    0.0059,
   -0.0035,
   -0.0003,
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



// the setup routine runs once when you press reset:
void setup() {
  Serial.begin(115200);
}

// the loop routine runs over and over again forever:
void loop() {
  // read the input on analog pin 0:
  sensorValue = analogRead(A0);
  sensorValue = sensorValue/1024*5 - 2.5;
  sensorValue = filter(sensorValue);
  
  // print out the value you read:
  Serial.println(sensorValue);
  delay(1);        // delay in between reads for stability
}



