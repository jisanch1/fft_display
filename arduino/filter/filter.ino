
/****** FILTER ******/
#define FILTER_LEN  20

double sensorValue;
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

// 120 Hz 
/*
const double coefs [FILTER_LEN] = {
  -0.002601570333142,
  -0.002361002964589,
   0.003888246457929,
   0.013997018307700,
   0.005671048820476,
  -0.033447515786797,
  -0.055772655206160,
   0.019548872679643,
   0.196840104536296,
   0.354237453488643,
   0.354237453488643,
   0.196840104536296,
   0.019548872679643,
  -0.055772655206160,
  -0.033447515786797,
   0.005671048820476,
   0.013997018307700,
   0.003888246457929,
  -0.002361002964589,
  -0.002601570333142,
};*/

/*
// 150 Hz
const double coefs [FILTER_LEN] = {
   0.002666823902708,
   0.000068099611685,
  -0.007450082876557,
  -0.002772578622813,
   0.023637748562748,
   0.015082103104625,
  -0.058649571323277,
  -0.057406613113769,
   0.159193872973760,
   0.425630197780891,
   0.425630197780891,
   0.159193872973760,
  -0.057406613113769,
  -0.058649571323277,
   0.015082103104625,
   0.023637748562748,
  -0.002772578622813,
  -0.007450082876557,
   0.000068099611685,
   0.002666823902708,
};*/

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
  delayMicroseconds(500);        // delay in between reads for stability
}



