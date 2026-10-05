#include <SPI.h>
#include <ESP8266WiFi.h>
#include <time.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>

// WiFi credentials
const char* ssid     = "shakerifard_2.4G";
const char* password = "RockyLinux";

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

const char* weekdays[] = {"Sat","Sun","Mon","Tue","Wed","Thu","Fri"};

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
  tft.print("Mon");

  tft.setTextColor(tft.color565(40,40,40));
  tft.setCursor(5, 40);
  tft.print("Tue");

  tft.setTextColor(tft.color565(40,40,40));
  tft.setCursor(5, 50);
  tft.print("Wed");

  tft.setTextColor(tft.color565(40,40,40));
  tft.setCursor(5, 60);
  tft.print("Thur");

  tft.setTextColor(tft.color565(40,40,40));
  tft.setCursor(5, 70);
  tft.print("Fri");

  tft.setTextColor(tft.color565(40,40,40));
  tft.setCursor(5, 80);
  tft.print("Sat");

  tft.setTextColor(tft.color565(40,40,40));
  tft.setCursor(5, 90);
  tft.print("Sun");

}

void loop() {
  time_t now = time(nullptr);
  struct tm* timeinfo = localtime(&now);

  char dateStr[15];  // YYY - MM - DD

  const char* weekdayName = weekdays[timeinfo->tm_wday];

  sprintf(dateStr, "%04d - %02d - %02d",
        timeinfo->tm_year + 1900,
        timeinfo->tm_mon + 1,
        timeinfo->tm_mday);

  int hour   = timeinfo->tm_hour;
  int minute = timeinfo->tm_min;
  int second = timeinfo->tm_sec;

  char hourStr[3];    // "08"
  char minStr[3];     // "41"
  
  sprintf(hourStr, "%02d", hour);
  sprintf(minStr, "%02d", minute);

  tft.setTextColor(ST77XX_WHITE);
  tft.setTextSize(4);
  tft.setCursor(35, 40);
  tft.print(hourStr);

  tft.setCursor(95, 40);
  tft.print(minStr);

  tft.setTextSize(1);
  tft.setCursor(40, 92);
  tft.println(dateStr);

  delay(500);
}
