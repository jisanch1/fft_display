#define BUF_LEN  32
#define OUT_LEN  BUF_LEN/2
#define FILTER_LEN  20
#define FFT_SIZE  32

int n;
double newval;
const double alpha = 0.5;

double input_buffer[FFT_SIZE];
double real_buffer[FFT_SIZE];
double imag_buffer[FFT_SIZE];
double magnitude_buffer[OUT_LEN];
double output_buffer[OUT_LEN];

void setup() {
  n = 0;
  Serial.begin(57600);
  timer_init();
}

void loop() {

}

void run()
{
  newval = analogRead(A0);
  newval /= 512;
  newval -= 1;
  newval *=2.5;
  //newval = filter(newval);
  if (n >= 0) input_buffer[n] = newval;
  n++;
  
  if (n >= BUF_LEN)
  {
    n = -FILTER_LEN;
    int j;
    
    dft(input_buffer, real_buffer, imag_buffer, FFT_SIZE);
    
    for (j = 0; j < OUT_LEN; j++)
    {
      magnitude_buffer[j] = sqrt(real_buffer[j]*real_buffer[j] + imag_buffer[j]*imag_buffer[j]);
      output_buffer[j] = (1 - alpha)*output_buffer[j] + alpha*magnitude_buffer[j];
    }

    for (j = 0; j < OUT_LEN - 1; j++)
    {
      Serial.print(output_buffer[j]);
      Serial.print(",");
    }
    Serial.println(output_buffer[j]);
    
  }
}

