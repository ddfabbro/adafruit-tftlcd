void loop(void) {
  byte state = 0;
  bool touch_event = false;

  touch_event = false;
  
  if (state == 0) {
    homeGUI();
    while (touch_event == false) {
      update_readings();
      switch_mode();
      TSPoint p = ts.getPoint();
      switch_mode();
      if (p.z > MINPRESSURE && p.z < MAXPRESSURE) {
        if (p.y < 300) {
          tft.fillRect(0, 96, 320, 240, WHITE);
          state = 1;
          touch_event = true;
        }
      }
    }
  }
  
  if (state == 1) {
    menuGUI();
    while (touch_event == false) {
      update_readings();
      switch_mode();
      TSPoint p = ts.getPoint();
      switch_mode();
      if (p.z > MINPRESSURE && p.z < MAXPRESSURE) {
        touch_event = true;
        if (p.y > 700) {
          state = 0; 
        }
        else if (p.y > 300) {
          tft.fillRect(0, 96, 320, 240, WHITE);
          state = 2;
        }
        else {
          tft.fillRect(0, 96, 320, 240, WHITE);
          state = 3;
        }
      }
    }
  }

  if (state == 2) {
    settingsGUI();
    while (touch_event == false) {
      update_readings();
      switch_mode();
      TSPoint p = ts.getPoint();
      switch_mode();
      if (p.z > MINPRESSURE && p.z < MAXPRESSURE) {
        touch_event = true;
        if (p.y > 700) {
          state = 0;
        }
        else if (p.y > 300) {
          if (p.x > 500) {
            temperature_target = temperature_target + 1;
            update_temperature_target();
          }
          else {
            temperature_target = temperature_target - 1;
            update_temperature_target();
          }
        }
        else {
          if (p.x > 500) {
            temperature_target = temperature_target + .1;
            update_temperature_target();
          }
          else {
            temperature_target = temperature_target - .1;
            update_temperature_target();
          }
        }
      }
    }
  }

  if (state == 3) {
    settingsGUI();
    while (touch_event == false) {
      update_readings();
      switch_mode();
      TSPoint p = ts.getPoint();
      switch_mode();
      if (p.z > MINPRESSURE && p.z < MAXPRESSURE) {
        touch_event = true;
        if (p.y > 700) {
          state = 0;
        }
        else if (p.y > 300) {
          if (p.x > 500) {
            humidity_target = humidity_target + 1;
            update_humidity_target();
          }
          else {
            humidity_target = humidity_target - 1;
            update_humidity_target();
          }
        }
        else {
          if (p.x > 500) {
            humidity_target = humidity_target + .1;
            update_humidity_target();
          }
          else {
            humidity_target = humidity_target - .1;
            update_humidity_target();
          }
        }
      }
    }
  }
}
