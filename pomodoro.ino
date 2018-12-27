#include <LiquidCrystal.h>

#include "../controller.h"

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
Controller controller{};

void setup() {
  lcd.begin(16, 2);
}

void loop() {
  controller.loop(millis(), false);
  lcd.setCursor(0, 0);
  lcd.print(controller.getTopLine());
  lcd.setCursor(0, 1);
  lcd.print(controller.getBottomLine());
  
  delay(100);
}
