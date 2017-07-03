struct freqPhase
{
  double freq;
  double fase;
};

// escribir las frecuencias de MENOR a MAYOR
struct freqPhase phaseList[] = {
  { 60, twopi/2},
  { 100, twopi/10},
  { 200, twopi/10}
};

const int phListLen = sizeof(phaseList)/sizeof(freqPhase);

double getPhase(double freq)
{
  int j;
  for (j = 0; j < phListLen; j++)
  {
    if (phaseList[j].freq > freq)
    {
      return phaseList[j].fase;
    }
  }
  return 0;
}


