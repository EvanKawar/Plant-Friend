#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SSD1306Ascii.h>
#include <SSD1306AsciiWire.h>

#define MOISTURE_PIN A0
#define DRY_VAL      450
#define WET_VAL      150
#define SD_CS_PIN    10

SSD1306AsciiWire oled;
bool sdAvailable = false;

void setup() {
  Serial.begin(9600);
  Wire.begin();
  oled.begin(&Adafruit128x64, 0x3C);
  oled.setFont(System5x7);
  oled.clear();
  sdAvailable = SD.begin(SD_CS_PIN);
  Serial.println(sdAvailable ? F("SD OK") : F("SD FAILED"));
}

void loop() {
  int raw = analogRead(MOISTURE_PIN);
  int pct = constrain(map(raw, DRY_VAL, WET_VAL, 0, 100), 0, 100);

  const char* status;
  if (pct < 45)       status = "LOW     ";
  else if (pct <= 70) status = "GOOD    ";
  else                status = "TOO HIGH";

  char moistureLine[22];
  char statusLine[22];
  sprintf(moistureLine, " |  %03d%% MOISTURE  | ", pct);
  sprintf(statusLine,   " | STATUS: %-8s| ",       status);

  oled.home();
  oled.println(F("               \\|/  "));
  oled.println(F("  PLANT FRIEND  |    "));
  oled.println(F("               [^]   "));
  oled.println(F(" |-----------------| "));
  oled.println(F(" |RAPHINUS  SATIVUS| "));
  oled.println(moistureLine);
  oled.println(statusLine);
  oled.print(F(" |-----------------| "));

  Serial.print(F("raw=")); Serial.print(raw);
  Serial.print(F(" pct=")); Serial.println(pct);

  if (sdAvailable) {
    File logFile = SD.open("moisture.csv", FILE_WRITE);
    if (logFile) {
      logFile.print(raw);
      logFile.print(",");
      logFile.println(pct);
      logFile.close();
      Serial.println(F("SD write OK"));
    } else {
      Serial.println(F("SD open FAILED"));
    }
  }

  delay(5000);
}
