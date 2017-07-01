void timer_init()
{
  noInterrupts();           // disable all interrupts
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1  = 0;

  OCR1A = 50;            // 250 = 1KHz, 125 = 2kHz, 50 = 5kHz
  TCCR1B |= (1 << WGM12);   // CTC mode
  TCCR1B |= (1 << CS11) | (1 << CS10);    // 64 prescaler 
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

