void update_readings() {
  if((millis()-time) >= 1000) {
    time = millis();

    read_temperature();
    read_humidity();
  }
}

void read_temperature() {
  double new_temperature_real;
  
  int readVal = analogRead(sensorPin); 
  new_temperature_real = Thermistor(readVal);

  if (new_temperature_real != temperature_real) {
    tft.fillRect(160, 20, 58, 14, BLACK); tft.setTextColor(WHITE);
    tft.setCursor(160, 20); tft.println(new_temperature_real);
    temperature_real = new_temperature_real;
  }
}

void read_humidity() {
  float new_humidity_real;

  new_humidity_real = dht.readHumidity();

  if (new_humidity_real != humidity_real) {
    tft.fillRect(160, 60, 58, 14, BLACK); tft.setTextColor(WHITE);
    tft.setCursor(160, 60); tft.println(new_humidity_real);
    humidity_real = new_humidity_real;
  }
}

void update_temperature_target() {
  tft.fillRect(245, 20, 70, 14, BLACK); tft.setTextColor(WHITE);
  if (temperature_target > 99.9) {
    temperature_target = 99.9;
  }
  else if (temperature_target < -9.9) {
    temperature_target = -9.9;
  }
  tft.setCursor(245, 20); tft.println(temperature_target);
}

void update_humidity_target() {
  tft.fillRect(245, 60, 70, 14, BLACK); tft.setTextColor(WHITE);
  if (humidity_target > 100) {
    humidity_target = 100;
  }
  else if (humidity_target < 0) {
    humidity_target = 0;
  }
  tft.setCursor(245, 60); tft.println(humidity_target);
}
