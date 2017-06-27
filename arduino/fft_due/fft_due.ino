double readDouble(char delim)
{
  String buf = Serial1.readStringUntil(delim);
  return buf.toFloat();
}

void printfft(double *output_buf, int n)
{
  int j;
  for (j = 0; j < n/2 - 1; j++)
    {
      Serial.print(output_buf[j]);
      Serial.print(",");
    }
    Serial.println(output_buf[j]);
}

#define FFT_SIZE  64
#define JUMPS     8

double input_buffer[FFT_SIZE];
double real_buffer[FFT_SIZE];
double imag_buffer[FFT_SIZE];
double output_buffer[FFT_SIZE];

double newval;
double maxval;
int maxpos;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial1.begin(115200);
  Serial1.setTimeout(1);
}

void loop() {
  // put your main code here, to run repeatedly:
  int j, k;
  for (j = 0; j < FFT_SIZE; j++)
  {
    for (k = 0; k < JUMPS; k++)
    {
      while(!Serial1.available()) 
        delayMicroseconds(5);
      if (k == 0) 
        input_buffer[j] = readDouble('&');
      else 
        readDouble('&');
    }
  }
  
  dft(input_buffer, real_buffer, imag_buffer, FFT_SIZE);
  maxpos = mag(output_buffer, real_buffer, imag_buffer, FFT_SIZE);
  printfft(output_buffer, FFT_SIZE);
  
}

/** 
 *  Para Obener frecuancia cada 4 Hz:
 *  fs = 2048
 *  Ps = 8
 *  N = 64
 *  Ts = 488n
 *  
*/








