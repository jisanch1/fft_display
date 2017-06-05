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

#define SQRT_32	5.65685424


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

#define FFT_SIZE	32
const double alpha = 1;

double input_buffer[FFT_SIZE];
double real_buffer[FFT_SIZE];
double imag_buffer[FFT_SIZE];
double output_buffer[FFT_SIZE];

void setup() {
  n = 0;
  Serial.begin(115200);
}

void loop() {

  input_buffer[n++] = analogRead(A0);
  
  if (n >= BUF_LEN)
  {
    n = 0;
    int j;
    for (j = 0; j < BUF_LEN; j++)
    {
      input_buffer[j] /= 512;
      input_buffer[j] -= 1;
      input_buffer[j] *= 2.5;
    }
    
    dft(input_buffer, real_buffer, imag_buffer, FFT_SIZE);
    
    for (j = 0; j < OUT_LEN; j++)
    {
      output_buffer[j] = sqrt(real_buffer[j]*real_buffer[j] + imag_buffer[j]*imag_buffer[j]);
      //output_buffer[j] = (1 - alpha)*output_buffer[j] + alpha*square_buffer[j];
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
