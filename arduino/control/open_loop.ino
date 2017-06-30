/****** open loop ********/
const double min_res = 5600;
const double fourpi = 12.566371;
const double twopi = 12.566371/2;
int check;
int switch_pos;

double pos;
double stepp;
double amp;
double gain;
double phase;

void open_loop_init()
{
    pos = 0;
    check = 0;
    gain = 1;
}

void open_loop()
{
  if (check % 100 == 0)
    {
      stepp = analogRead(A0);
      stepp /= min_res;
      gain = analogRead(A1);
      gain /= 1024;
      phase = analogRead(A2);
      phase /= 512;
      phase -= 1;
      phase *= twopi;
      check = 0;
    }
    
    pos += stepp;
    if (pos > fourpi)  pos -= fourpi;
    amp = sin(pos + phase);
    amp *= gain;
    amp += 1;
    amp *= 2048;
    
    dac_val = (unsigned int)amp;
    dac_write(dac_val);

    check++;
}
