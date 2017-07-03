/****** FILTER ******/


double sensorValue;
double filter_buf[FILTER_LEN];

// 120 Hz 
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
/*****/
