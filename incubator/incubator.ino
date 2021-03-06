#include <SPFD5408_Adafruit_GFX.h>
#include <SPFD5408_Adafruit_TFTLCD.h>
#include <SPFD5408_TouchScreen.h>
#include <DHT.h>
#include <math.h>

//define TouchScreen pins
#define YP A1
#define XM A2
#define YM 7
#define XP 6

//define TFTLCD pins
#define LCD_RD A0
#define LCD_WR A1
#define LCD_CD A2
#define LCD_CS A3
#define LCD_RESET A4

//define DHT pin
#define DHTPIN 52

//define thermistor
#define ThermistorPIN A8

//define other variables
#define MINPRESSURE 10
#define MAXPRESSURE 1000
#define BLACK           0xFFFF //0x0000
#define WHITE           0x0000 //0xFFFF

byte state = 0;
bool touch_event = false;
bool uv_led = true;

float temperature_real;
float temperature_target = 25;
float humidity_real;
unsigned long time;

TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);
Adafruit_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);
DHT dht(DHTPIN, DHT11);

void reconfig() {
  pinMode(XM, OUTPUT);
  pinMode(YP, OUTPUT);
}

void setup(void) {
  tft.reset();
  uint16_t identifier = 0x9341;
  dht.begin();
  tft.begin(identifier);
  tft.fillScreen(BLACK);
  tft.setRotation(1);
  tft.setTextSize(2);
  
  temperature_real = readThermistor();
  humidity_real = dht.readHumidity();

  monitor();
  
  time=millis();
}
