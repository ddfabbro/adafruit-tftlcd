void monitor() {
  tft.setTextColor(WHITE);
  
  tft.setCursor(10, 20); tft.println("TEMPERATURE:      /");
  tft.setCursor(160, 20); tft.println(temperature_real);
  tft.setCursor(245, 20); tft.println(temperature_target);

  tft.setCursor(10, 60); tft.println("HUMIDITY:         /");
  tft.setCursor(160, 60); tft.println(humidity_real);
  tft.setCursor(245, 60); tft.println(humidity_target);
}

void homeGUI() {
  tft.fillRect(0, 96, 320, 168, BLACK); tft.setTextColor(WHITE);
  
  tft.setCursor(10, 100); tft.println("TEMPERATURE FAN:");
  if (temperature_fan == true) {
    tft.setCursor(215, 100); tft.println("ON");
  }
  else {
    tft.setCursor(215, 100); tft.println("OFF");
  }
  
  tft.setCursor(10, 140); tft.println("HUMIDITY FAN:");
  if (humidity_fan == true) {
    tft.setCursor(180, 140); tft.println("ON");
  }
  else {
    tft.setCursor(180, 140); tft.println("OFF");
  }
  
  tft.fillRect(0, 168, 320, 240, WHITE);
  tft.setTextColor(BLACK);tft.setCursor(110, 195); tft.println("SETTINGS");
}

void menuGUI() {
  tft.setTextColor(BLACK); 
  tft.setCursor(75, 125); tft.println("SET TEMPERATURE");
  tft.setCursor(90, 195); tft.println("SET HUMIDITY");
  tft.drawLine(0,168,320,168,BLACK);
}

void settingsGUI() {
  tft.setTextColor(BLACK); 
  tft.setCursor(60, 125); tft.println("- x1");
  tft.setCursor(210, 125); tft.println("+ x1");
  tft.setCursor(60, 195); tft.println("- x0.1");
  tft.setCursor(210, 195); tft.println("+ x0.1");
  tft.drawLine(0,168,320,168,BLACK);
  tft.drawLine(160,96,160,240,BLACK);
}

void update_sensor_values() {
  tft.fillRect(160, 20, 58, 14, BLACK); tft.setTextColor(WHITE);
  tft.setCursor(160, 20); tft.println(temperature_real);

  tft.fillRect(160, 60, 58, 14, BLACK); tft.setTextColor(WHITE);
  tft.setCursor(160, 60); tft.println(humidity_real);
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
