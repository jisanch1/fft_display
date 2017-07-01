/****** FILTER ******/
double previous;
double alpha = 0.5;

double expfilter(double in)
{
  return alpha*in + (1-alpha)*previous;
}

double distance(double acc, double dist, double dt)
{
  double vel = acc*dt;
  dist = 0.4*dist + vel*dt + 0.5*acc*dt*dt;
  return dist;
}


#define FILTER_LEN  25

double filter_buf[FILTER_LEN];
double mini_buf[3];

const double coef100 [FILTER_LEN] = {
  -0.00203366, 
  -0.00285366, 
  -0.00139087, 
  0.00452641, 
  0.01127242, 
  0.00727871, 
  -0.01541559, 
  -0.04379573, 
  -0.04253021, 
  0.02009486, 
  0.13723587, 
  0.25466474, 
  0.30412088, 
  0.25466474, 
  0.13723587, 
  0.02009486, 
  -0.04253021, 
  -0.04379573, 
  -0.01541559, 
  0.00727871, 
  0.01127242, 
  0.00452641, 
  -0.00139087, 
  -0.00285366, 
  -0.00203366, 
};

const double coef1 [] = {
  0.06896460, 
  0.86207081, 
  0.06896460, 
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
    ret += coef100[i] * filter_buf[i];
  }

  return ret;
}

double integrator(double new_val)
{
  
  // se despazan los valores en 1
  int i;
  for (i = 3 - 1; i > 0; i--)
  {
    mini_buf[i] = mini_buf[i-1];
  }

  // se asigna el nuevo valor
  mini_buf[0] = new_val;

  //se calcula el valor de salida
  double ret = 0;
  for (i = 0; i < 3; i++)
  {
    ret += coef1[i] * mini_buf[i];
  }

  return ret;
}
