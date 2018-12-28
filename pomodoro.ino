#include <LiquidCrystal.h>

#define COMPILE_FOR_DEVICE true

#include "libraries/controller.h"
#include "libraries/util.h"

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
Controller controller{ms(25, 0), ms(5, 0)};

void setup() {
  lcd.begin(16, 2);
  pinMode(7, INPUT);
  Serial.begin(9600);
  controller.begin();
}

void loop() {
  controller.loop(millis(), digitalRead(7));
  lcd.setCursor(0, 0);
  lcd.print(controller.getTopLine());
  lcd.setCursor(0, 1);
  lcd.print(controller.getBottomLine());
  
  delay(500);
}
