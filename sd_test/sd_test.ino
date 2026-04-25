#include <SD.h>
#include <SPI.h>

#define CS_PIN 10

void setup() {
  Serial.begin(9600);
  Serial.println("Testing SD...");
  if (!SD.begin(CS_PIN)) {
    Serial.println("SD init failed!");
  } else {
    Serial.println("SD init OK!");
  }
}

void loop() {}

