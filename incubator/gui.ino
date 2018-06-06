void monitor() {
  tft.setTextColor(WHITE);
  
  tft.setCursor(10, 20); tft.println("TEMPERATURE:      /");
  tft.setCursor(160, 20); tft.println(temperature_real);
  tft.setCursor(245, 20); tft.println(temperature_target);

  tft.setCursor(10, 60); tft.println("HUMIDITY:         %");
  tft.setCursor(160, 60); tft.println(humidity_real);
}

void homeGUI() {
  tft.fillRect(0, 96, 320, 168, BLACK);
  tft.setTextColor(WHITE);
  tft.setCursor(10, 100); tft.println("UV LED:");
  if (uv_led == true) {
    tft.setCursor(215, 100); tft.println("ON");
  }
  else {
    tft.setCursor(215, 100); tft.println("OFF");
  }
  tft.fillRect(0, 168, 320, 240, WHITE);
  tft.setTextColor(BLACK);tft.setCursor(110, 195); tft.println("SETTINGS");
}

void menuGUI() {
  tft.setTextColor(BLACK); 
  tft.setCursor(75, 125); tft.println("SET TEMPERATURE");
  tft.setCursor(90, 195); tft.println("SET UV LED");
  tft.drawLine(0,168,320,168,BLACK);
}

void setTemperatureGUI() {
  tft.setTextColor(BLACK); 
  tft.setCursor(60, 125); tft.println("- x1");
  tft.setCursor(210, 125); tft.println("+ x1");
  tft.setCursor(60, 195); tft.println("- x0.1");
  tft.setCursor(210, 195); tft.println("+ x0.1");
  tft.drawLine(0,168,320,168,BLACK);
  tft.drawLine(160,96,160,240,BLACK);
}

void setUVLEDGUI() {
  tft.setTextColor(WHITE);
  tft.setCursor(10, 100); tft.println("UV LED:");
  if (uv_led == true) {
    tft.setCursor(215, 100); tft.println("ON");
  }
  else {
    tft.setCursor(215, 100); tft.println("OFF");
  }
  
  tft.setTextColor(BLACK); 
  tft.setCursor(60, 195); tft.println("OFF");
  tft.setCursor(210, 195); tft.println("ON");
  tft.drawLine(160,168,160,240,BLACK);
}
