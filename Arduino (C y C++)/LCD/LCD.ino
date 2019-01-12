#include <LiquidCrystal.h>

LiquidCrystal lcd(22, 23, 24, 25, 26, 27, 28);

void setup (void) {
	lcd.begin(16, 2);
}

void loop (void) {
	lcd.clear();
	lcd.setCursor(3, 0);
	lcd.print("Welcome to");
	lcd.setCursor(1, 1);
	lcd.print("geek-workshop");
	delay(5000);
	lcd.clear();
	lcd.setCursor(0, 0);
	lcd.print("I am hongyi_");
	delay(5000);
}