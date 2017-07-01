

void timer_init()
{
  noInterrupts();           // disable all interrupts
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1  = 0;

  OCR1A = 800;             // 2000 = 1KHz, 1000 = 2kHz, 800 = 2.5kHz, 400 = 5kHz (2000 / KHz)
  TCCR1B |= (1 << WGM12);   // CTC mode
  TCCR1B |= (1 << CS11);    // 8 prescaler 
  TIMSK1 |= (1 << OCIE1A);  // enable timer compare interrupt
  interrupts();             // enable all interrupts
}


ISR(TIMER1_COMPA_vect)
{
  noInterrupts();
  muestreo();
  //blinka();
  interrupts();
}

int asd = 0;
int qwe = 0;
void blinka()
{
  if (asd >= 1000)
  {
    if (qwe == 1)
    {
      digitalWrite(INPUT_PIN, LOW);
      qwe = 0;
    }
    else
    {
      digitalWrite(INPUT_PIN, HIGH);
      qwe = 1;
    }
    asd = 0;
  }
  asd++;
}

