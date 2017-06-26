#include <Wire.h>

const double tsin[] = {
	0.0,
	0.19509032,
	0.38268343,
	0.55557023,
	0.70710678,
	0.83146961,
	0.92387953,
	0.98078528,
	1.0,
	0.98078528,
	0.92387953,
	0.83146961,
	0.70710678,
	0.55557023,
	0.38268343,
	0.19509032,
	0.0,
	-0.19509032,
	-0.38268343,
	-0.55557023,
	-0.70710678,
	-0.83146961,
	-0.92387953,
	-0.98078528,
	-1.0,
	-0.98078528,
	-0.92387953,
	-0.83146961,
	-0.70710678,
	-0.55557023,
	-0.38268343,
	-0.19509032
};

const double tcos[] = {
	1.0,
	0.98078528,
	0.92387953,
	0.83146961,
	0.70710678,
	0.55557023,
	0.38268343,
	0.19509032,
	0.0,
	-0.19509032,
	-0.38268343,
	-0.55557023,
	-0.70710678,
	-0.83146961,
	-0.92387953,
	-0.98078528,
	-1.0,
	-0.98078528,
	-0.92387953,
	-0.83146961,
	-0.70710678,
	-0.55557023,
	-0.38268343,
	-0.19509032,
	0.0,
	0.19509032,
	0.38268343,
	0.55557023,
	0.70710678,
	0.83146961,
	0.92387953,
	0.98078528,
};

/****** FILTER ******/
#define FILTER_LEN  20

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

void delay320Hz(void)
{
  int i;
  for (i = 0; i < 25; i++)
  {
    delayMicroseconds(125);
  }
}

void dft(double *input_buf, double *real_buf, double *imag_buf, int n)
{
	uint16_t i, j, k;
	for (i = 0; i < n; i++)
	{
		real_buf[i] = 0;
		imag_buf[i] = 0;
		for (j = 0; j < n; j++)
		{
			k = (i*j) % n;
			real_buf[i] += input_buf[j]*tcos[k];
			imag_buf[i] -= input_buf[j]*tsin[k];
		}
	}
}

#define BUF_LEN  32
#define OUT_LEN  BUF_LEN/2

int n;
double newval;
double maxval;
int maxpos;

#define FFT_SIZE	32
const double alpha = 1;

double input_buffer[FFT_SIZE];
double real_buffer[FFT_SIZE];
double imag_buffer[FFT_SIZE];
double output_buffer[FFT_SIZE];

void setup() {
  n = 0;
  maxval = 0;
  Serial.begin(115200);
  Wire.begin(8);                // join i2c bus with address #8
  Wire.onRequest(requestEvent); // register event
}

void loop() {

  newval = analogRead(A0);
  newval /= 512;
  newval -= 1;
  newval *=2.5;
  newval = filter(newval);
  if (n >= 0) input_buffer[n] = newval;
  n++;
  
  if (n >= BUF_LEN)
  {
    n = -FILTER_LEN;
    int j;
    
    dft(input_buffer, real_buffer, imag_buffer, FFT_SIZE);
    
    for (j = 0; j < OUT_LEN; j++)
    {
      output_buffer[j] = sqrt(real_buffer[j]*real_buffer[j] + imag_buffer[j]*imag_buffer[j]);
      //output_buffer[j] = (1 - alpha)*output_buffer[j] + alpha*square_buffer[j];
    }

    for (j = 0; j < OUT_LEN; j++)
    {
      if (output_buffer[j] > maxval)
      {
        maxval = output_buffer[j];
        maxpos = j;
      }
    }
    
    for (j = 0; j < OUT_LEN - 1; j++)
    {
      Serial.print(output_buffer[j]);
      Serial.print(",");
    }
    Serial.println(output_buffer[j]);
    
  }
  
  delay(4);   
}

/*** I2C request ***/

void requestEvent(void)
{
  Wire.write((unsigned char)maxpos);
}
