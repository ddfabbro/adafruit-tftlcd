float readThermistor() {
  float Temp;
  int readVal = analogRead(ThermistorPIN);
  
  Temp = log(10000.0*((1024.0/readVal-1))); 
  Temp = 1 / (0.001129148 + (0.000234125 + (0.0000000876741 * Temp * Temp ))* Temp );
  Temp = Temp - 273.15;

  return Temp;
}
