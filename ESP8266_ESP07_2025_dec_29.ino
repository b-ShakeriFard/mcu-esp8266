#include <Wire.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_ST7789.h>

// ---------- OLED ----------
#define OLED_SDA 4
#define OLED_SCL 5
#define OLED_ADDR 0x3C
Adafruit_SSD1306 oled(128, 64, &Wire, -1);

// ---------- TFT ----------
#define TFT_CS   15
#define TFT_DC   2
#define TFT_RST  16
Adafruit_ST7789 tft(TFT_CS, TFT_DC, TFT_RST);

// OLED animation
int oledX = 0;
int oledDir = 1;

// TFT animation
int boxX = 20, boxY = 20;
int dx = 3, dy = 2;
const int boxSize = 20;

void setup() {
  // OLED
  Wire.begin(OLED_SDA, OLED_SCL);
  oled.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  oled.clearDisplay();
  oled.display();

  // TFT
  tft.init(240, 280);       // adjust if needed
  tft.setRotation(1);
  tft.fillScreen(ST77XX_BLACK);
}

void loop() {

  // ----- OLED: moving dot -----
  oled.clearDisplay();
  oled.fillCircle(oledX, 32, 3, WHITE);
  oled.display();

  oledX += oledDir * 1.5;
  if (oledX <= 0 || oledX >= 127) {
    oledDir = -oledDir;
  }

  // ----- TFT: bouncing box -----
  tft.fillRect(boxX, boxY, boxSize, boxSize, ST77XX_BLACK);

  boxX += dx;
  boxY += dy;

  if (boxX <= 0 || boxX + boxSize >= tft.width())  dx = -dx;
  if (boxY <= 0 || boxY + boxSize >= tft.height()) dy = -dy;

  tft.fillRect(boxX, boxY, boxSize, boxSize, ST77XX_CYAN);

  delay(30);   // smooth but light
}
