void timer_init()
{
  TCCR0A |= _BV(WGM01); // CTC mode
  TCCR0B |= _BV(CS01) | _BV(CS00);  // prescaler 64
  OCR0A = 125;
  TIMSK0 |= _BV(OCIE0A);  // Enable interrupt
}


ISR(TIMER0_COMPA_vect)
{
  cli();
  //muestreo();
  blinka();
  sei();
}

int asd = 0;
int qwe = 0;
void blinka()
{
  if (asd >= 1000)
  {
    if (qwe == 1)
    {
      digitalWrite(LED_BUILTIN, LOW);
      qwe = 0;
    }
    else
    {
      digitalWrite(LED_BUILTIN, HIGH);
      qwe = 1;
    }
    asd = 0;
  }
  asd++;
}

