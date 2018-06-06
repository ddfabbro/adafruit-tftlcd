void updateReadings(float new_temperature_real, float new_humidity_real) {
  if((millis()-time) >= 1000) {
    time = millis();
    
    if (new_temperature_real != temperature_real) {
      tft.fillRect(160, 20, 58, 14, BLACK); tft.setTextColor(WHITE);
      tft.setCursor(160, 20); tft.println(new_temperature_real);
      temperature_real = new_temperature_real;
    }

    if (new_humidity_real != humidity_real) {
      tft.fillRect(160, 60, 58, 14, BLACK); tft.setTextColor(WHITE);
      tft.setCursor(160, 60); tft.println(new_humidity_real);
      humidity_real = new_humidity_real;
    }
  }
}

void updateTemperatureTarget() {
  tft.fillRect(245, 20, 70, 14, BLACK); tft.setTextColor(WHITE);
  if (temperature_target > 99.9) {
    temperature_target = 99.9;
  }
  else if (temperature_target < -9.9) {
    temperature_target = -9.9;
  }
  tft.setCursor(245, 20); tft.println(temperature_target);
}

void updateUVTarget() {
  tft.fillRect(215, 100, 70, 14, BLACK); tft.setTextColor(WHITE);
  tft.setCursor(215, 100); 
  if (uv_led == true) {
    tft.setCursor(215, 100); tft.println("ON");
  }
  else {
    tft.setCursor(215, 100); tft.println("OFF");
  }

}

