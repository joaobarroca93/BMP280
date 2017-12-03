#include <BMP280.h>

BMP280 bmp;

void setup() {
  Serial.begin(9600);
  while (!bmp.begin()) {  
    Serial.println(F("Error initializing BMP280!"));
    delay(1000);
  }
}

void loop() {
  Serial.print(bmp.readTemperature());
  Serial.print(" | ");
  Serial.print(bmp.readPressure());
  Serial.print(" | ");
  Serial.println(bmp.readAltitude());
  /* use a sampling time of at least 38ms */
  delay(50);
}
