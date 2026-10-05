
#include <SPI.h>
#include <ESP8266WiFi.h>
#include <time.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>

// WiFi credentials
const char* ssid     = "HA6400_B93C";
const char* password = "b2bdfd495d";

// Time settings
const char* ntpServer = "pool.ntp.org";
const long  gmtOffset_sec = 12600;        // UTC
const int   daylightOffset_sec = 0;   // no DST for now

// Pin mapping
#define TFT_CS   15   // GPIO15
#define TFT_DC   2   // GPIO2
#define TFT_RST  0   // GPIO0

// Create display object
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);

void setup() {
  Serial.begin(115200);

  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nWiFi connected");

  // Initialize NTP
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);

  Serial.print("Waiting for time sync");
  time_t now = time(nullptr);
  while (now < 100000) {
    delay(500);
    Serial.print(".");
    now = time(nullptr);
  }

  Serial.println("\nTime synced");
  Serial.println("ST7735 Test");

  tft.initR(INITR_BLACKTAB);   // Most 0.96" displays use BLACKTAB
  tft.setRotation(3);

  tft.fillScreen(ST77XX_BLACK);

  tft.setTextColor(ST77XX_MAGENTA);
  tft.setTextSize(1);
  tft.setCursor(5, 30);
  tft.println("Mon");

}

void loop() {
  time_t now = time(nullptr);
  struct tm* timeinfo = localtime(&now);

  Serial.printf(
    "%04d-%02d-%02d  %02d:%02d:%02d  (weekday: %d)\n",
    timeinfo->tm_year + 1900,
    timeinfo->tm_mon + 1,
    timeinfo->tm_mday,
    timeinfo->tm_hour,
    timeinfo->tm_min,
    timeinfo->tm_sec,
    timeinfo->tm_wday
  );

  char timeStr[9];   // HH:MM:SS
  char dateStr[11];  // YYY-MM-DD

  sprintf(timeStr, "%02d:%02d:%02d",
        timeinfo->tm_hour,
        timeinfo->tm_min,
        timeinfo->tm_sec);

  tft.setTextColor(ST77XX_WHITE);
  tft.setTextSize(1);
  tft.setCursor(35, 40);
  tft.println(timeStr);

  delay(500);
}