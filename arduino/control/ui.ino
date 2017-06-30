struct par
{
  String nombre;
  double *var;
};

struct par valuesList[] = {
  {"Kp", &Kp},
  {"Ki", &Ki},
  {"Kd", &Kd}
};

const int listlen = sizeof(valuesList)/sizeof(par);

void serialEvent() 
{
  String cmd = Serial.readStringUntil(':');
  String nom;
  String val;
  if (cmd == "get")
  {
    nom = Serial.readStringUntil(';');
    getVar(nom);
  }
  else if (cmd == "set")
  {
    nom = Serial.readStringUntil('=');
    val = Serial.readStringUntil(';');
    setVar(nom, val.toFloat());
  }
  else
  {
    Serial.println("Error, command doesn't exist");
  }
}

int getVar(String nom)
{
  int j;
  for (j = 0; j < listlen; j++)
  {
    if (valuesList[j].nombre == nom)
    {
      Serial.print(nom);
      Serial.print(" = ");
      Serial.println(*valuesList[j].var);
      return 1;
    }
  }
  Serial.println("Error, variable doesn't exist");
  return -1;
}

int setVar(String nom, double var)
{
  int j;
  for (j = 0; j < listlen; j++)
  {
    if (valuesList[j].nombre == nom)
    {
      *valuesList[j].var = var;
      Serial.print(nom);
      Serial.print(" set to ");
      Serial.println(var);
      return 1;
    }
  }
  Serial.println("Error, variable doesn't exist");
  return -1;
}






