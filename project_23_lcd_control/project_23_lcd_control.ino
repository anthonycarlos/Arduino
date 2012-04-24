// PROJECT 23
#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup() {
  lcd.begin(16, 2);
}

void loop() {
  basicPrintDemo();
  displayOnOffDemo();
  setCursorDemo();
}

void basicPrintDemo() {
  lcd.clear();
  lcd.print("Basic Print");
  delay(2000);
}

void displayOnOffDemo() {
  lcd.clear();
  lcd.print("Display On/Off");
  for(int x=0; x < 3; x++) {
    lcd.noDisplay();
    delay(1000);
    lcd.display();
    delay(1000);
  }
}

void setCursorDemo() {
  lcd.clear();
  lcd.print("SetCursor Demo");
  delay(1000);
  lcd.clear();
  lcd.setCursor(5,0);
  lcd.print("5,0");
  delay(2000);
  lcd.setCursor(10,1);
  lcd.print("10,1");
  delay(2000);
  lcd.setCursor(3,1);
  lcd.print("3,1");
  delay(2000);
}
