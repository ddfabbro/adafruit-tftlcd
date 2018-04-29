float readThermistor() {
  float Temp;
  //int sensorPin = ThermistorPIN;
  int readVal = analogRead(ThermistorPIN);
  
  Temp = log(10000.0*((1024.0/readVal-1))); 
  Temp = 1 / (0.001129148 + (0.000234125 + (0.0000000876741 * Temp * Temp ))* Temp );
  Temp = Temp - 273.15;            // Convert Kelvin to Celcius
  //Temp = (Temp * 9.0)/ 5.0 + 32.0; // Convert Celcius to Fahrenheit

  return Temp;
}
