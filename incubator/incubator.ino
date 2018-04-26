#include <Adafruit_GFX.h> 
#include <Adafruit_TFTLCD.h>
#include <TouchScreen.h>

//define TouchScreen pins
#define YP A1
#define XM A2
#define YM 7
#define XP 6
#define MINPRESSURE 10
#define MAXPRESSURE 1000

TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);

//define TFTLCD pins
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

void switch_mode() {
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
