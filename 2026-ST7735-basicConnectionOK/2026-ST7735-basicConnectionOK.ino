#include <SPI.h>
#include <ESP8266WiFi.h>
#include <time.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>

// Pin mapping
#define TFT_CS   15   // GPIO15
#define TFT_DC   2   // GPIO2
#define TFT_RST  0   // GPIO0

// Create display object
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);

void setup() {
  Serial.begin(115200);
  Serial.println("ST7735 Test");

  tft.initR(INITR_BLACKTAB);   // Most 0.96" displays use BLACKTAB
  tft.setRotation(3);

  tft.fillScreen(ST77XX_BLACK);

  tft.setTextColor(ST77XX_GREEN);
  tft.setTextSize(2);
  tft.setCursor(10, 30);
  tft.println("Hello!");

  tft.setTextSize(1);
  tft.setCursor(10, 60);
  tft.setTextColor(ST77XX_WHITE);
  tft.println("ESP8266 + TFT");
}

void loop() {
  // nothing yet
}
