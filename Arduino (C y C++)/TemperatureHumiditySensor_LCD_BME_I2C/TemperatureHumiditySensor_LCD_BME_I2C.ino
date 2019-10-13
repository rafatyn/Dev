#include <Wire.h>
#include <SPI.h>
#include <LiquidCrystal_I2C.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

#define SEALEVELPRESSURE_HPA (1013.25)

// BME280 I2C
Adafruit_BME280 bme;

// LCD I2C
LiquidCrystal_I2C lcd(0x27,16,2);

void setup() {
  unsigned status = bme.begin();  
  if (!status) {
    Serial.begin(9600);
    while(!Serial);
    Serial.println("Could not find a valid BME280 sensor, check wiring, address, sensor ID!");
    Serial.print("SensorID was: 0x"); Serial.println(bme.sensorID(),16);
    Serial.print("        ID of 0xFF probably means a bad address, a BMP 180 or BMP 085\n");
    Serial.print("   ID of 0x56-0x58 represents a BMP 280,\n");
    Serial.print("        ID of 0x60 represents a BME 280.\n");
    Serial.print("        ID of 0x61 represents a BME 680.\n");
    while (1);
  }

  lcd.init();
  lcd.backlight();
}

void loop() {
  lcd.setCursor(0, 0);
  
  lcd.print("Tmp: ");
  lcd.print(bme.readTemperature());
  lcd.print("C");

  lcd.setCursor(0, 1);
  
  lcd.print("Hm: ");
  lcd.print(round(bme.readHumidity()));
  lcd.print("%");

  lcd.setCursor(9, 1);
  
  lcd.print("Al: ");
  lcd.print(round(bme.readAltitude(SEALEVELPRESSURE_HPA)));
  lcd.print("m");
  
  delay(1000);
}
