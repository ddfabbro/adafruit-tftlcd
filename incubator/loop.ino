void loop(void) {
  touch_event = false;
  
  if (state == 0) {
    homeGUI();
    while (touch_event == false) {
      reconfig();
      TSPoint p = ts.getPoint();
      reconfig();
      updateReadings(readThermistor(),dht.readHumidity());

      if (temperature_real > temperature_target) {
        cool();
      }

      else {
        heat();
      }
      
      if (p.z > MINPRESSURE && p.z < MAXPRESSURE) {
        if (p.y < 360) {
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
      reconfig();
      TSPoint p = ts.getPoint();
      reconfig();
      if (p.z > MINPRESSURE && p.z < MAXPRESSURE) {
        touch_event = true;
        if (p.y > 600) {
          state = 0; 
        }
        else if (p.y > 360) {
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
      reconfig();
      TSPoint p = ts.getPoint();
      reconfig();
      if (p.z > MINPRESSURE && p.z < MAXPRESSURE) {
        touch_event = true;
        if (p.y > 600) {
          state = 0;
        }
        else if (p.y > 360) {
          if (p.x > 530) {
            temperature_target = temperature_target + 1;
            updateTemperatureTarget();
          }
          else {
            temperature_target = temperature_target - 1;
            updateTemperatureTarget();
          }
        }
        else {
          if (p.x > 530) {
            temperature_target = temperature_target + .1;
            updateTemperatureTarget();
          }
          else {
            temperature_target = temperature_target - .1;
            updateTemperatureTarget();
          }
        }
      }
    }
  }

  if (state == 3) {
    settingsGUI();
    while (touch_event == false) {
      reconfig();
      TSPoint p = ts.getPoint();
      reconfig();
      if (p.z > MINPRESSURE && p.z < MAXPRESSURE) {
        touch_event = true;
        if (p.y > 600) {
          state = 0;
        }
        else if (p.y > 360) {
          if (p.x > 530) {
            humidity_target = humidity_target + 1;
            updateHumidityTarget();
          }
          else {
            humidity_target = humidity_target - 1;
            updateHumidityTarget();
          }
        }
        else {
          if (p.x > 530) {
            humidity_target = humidity_target + .1;
            updateHumidityTarget();
          }
          else {
            humidity_target = humidity_target - .1;
            updateHumidityTarget();
          }
        }
      }
    }
  }
}
