#include <Adafruit_GFX.h> 
#include <Adafruit_TFTLCD.h>
#include <TouchScreen.h>

//define TouchScreen variables
#define YP A1
#define XM A2
#define YM 7
#define XP 6
#define MINPRESSURE 10
#define MAXPRESSURE 1000

TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);

//define TFTLCD variables
#define LCD_CS A3
#define LCD_CD A2
#define LCD_WR A1
#define LCD_RD A0
#define LCD_RESET A4
#define BLACK           0xFFFF //0x0000
#define WHITE           0x0000 //0xFFFF

Adafruit_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);

byte state = 0;
float temperature_real = 25.1;
float temperature_target = 25.4;
float humidity_real = 70.6;
float humidity_target = 70.2;
bool temperature_fan = true;
bool humidity_fan = false;
bool touch_event = false;

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

void update_temperature_real() {
  tft.fillRect(160, 20, 58, 14, BLACK); tft.setTextColor(WHITE);
  tft.setCursor(160, 20); tft.println(temperature_real);
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

void update_humidity_real() {
  tft.fillRect(160, 60, 58, 14, BLACK); tft.setTextColor(WHITE);
  tft.setCursor(160, 60); tft.println(humidity_real);
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

void reconfig() {
  pinMode(XM, OUTPUT);
  pinMode(YP, OUTPUT);
}

void setup(void) {
  Serial.begin(9600);
  tft.reset();
  uint16_t identifier = 0x9341;
  tft.begin(identifier);
  tft.fillScreen(BLACK);
  tft.setRotation(1);
  tft.setTextSize(2);
  monitor();
}

void loop(void) {
  touch_event = false;

  if (state == 0) {
    homeGUI();
    while (touch_event == false) {
      reconfig();
      TSPoint p = ts.getPoint();
      reconfig();
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
      reconfig();
      TSPoint p = ts.getPoint();
      reconfig();
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
      reconfig();
      TSPoint p = ts.getPoint();
      reconfig();
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
      reconfig();
      TSPoint p = ts.getPoint();
      reconfig();
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


