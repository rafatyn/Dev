#include <CircularBuffer.h>
#include <DHT.h>
#include <LiquidCrystal.h>

LiquidCrystal lcd(22, 23, 24, 25, 26, 27, 28);
DHT dht11(12, 11);
float voltage = 0;
CircularBuffer<float, 10> buffer;
unsigned long voltMillis = 0, tempMillis = 0, lcdMillis = 0;
int temperature = 0, humidity = 0, light = 0;

void setup (void) {
	lcd.begin(16, 2);
	dht11.begin();
	Serial.begin(9600);
}

void loop (void) {
	if (millis() - voltMillis > 50) {
		voltMillis = millis();
		voltage = static_cast<float>(analogRead(1)) * 50 / 1024;
		buffer.push(voltage);
	}
	
	if (millis() - tempMillis > 1000) {
		tempMillis = millis();
		if (dht11.read()) {
			temperature = dht11.readTemperature();
			humidity = dht11.readHumidity();
			light = 100 - (static_cast<float>(analogRead(0)) * 100 / 1024);
		}
	}
		
		
	if(millis() - lcdMillis > 500) {
		float volta = 0;
		for (int i = 0; i < buffer.size(); i++) {
			volta += buffer[i];
		}

		lcd.clear();
		lcd.setCursor(0, 0);
		lcd.print("Tmp:");
		lcd.print(temperature);
		lcd.print("C");
		lcd.setCursor(10, 0);
		lcd.print("Lh:");
		lcd.print(light);
		lcd.print("%");
		lcd.setCursor(0, 1);
		lcd.print("Hum:");
		lcd.print(humidity);
		lcd.print("%");
		lcd.setCursor(11, 1);		
		lcd.print(volta / buffer.size());
		lcd.print("V");
		delay(500);
	}
}
