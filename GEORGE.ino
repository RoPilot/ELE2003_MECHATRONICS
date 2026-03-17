// DEINE PACKAGES
#include <LiquidCrystal.h>
#include <Servo.h>

// DEFINE PINS, EASY FOR PROTOTYPING AND DEBUGGING
const int SERVO1  = 6;
const int POTENTIOMETER    = A0;
const int PUSHBUTTON = 7;
const int LED1    = 8;

// CREATE NEW LCD INSTANCE
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
// CREATE SERVO INSTANCE
Servo motor;

// INIT SETUP
void setup() {
  lcd.begin(16, 2); // START LCD WITH 16X2 GRID
  motor.attach(SERVO1); // REFERENCE PIN D6 TO MOTOR

  pinMode(PUSHBUTTON, INPUT_PULLUP);
  pinMode(LED1, OUTPUT);

  lcd.clear(); // CLEAR LCD
}

// CODE LOOP
void loop() {

  // HANDLE BUTTON PRESS
  if (digitalRead(PUSHBUTTON) == LOW) {
    lcd.clear();
    lcd.print("STAMPING IN PROG");

    // MOVE THE SERVO BY 180 DEGREES & FLASH LED
    // BELOW, FLASH LED
    for (int i = 0; i < 5; i++) {
      digitalWrite(LED1, HIGH);
      delay(100);
      digitalWrite(LED1, LOW);
      delay(100);
    }

    motor.write(180); // MOVE SERVO
    lcd.setCursor(0, 1);
    lcd.print("Angle: 180");
    delay(2000);

    // MOVE THE SERVO BY 180 DEGREES & FLASH LED
    // BELOW, FLASH LED
    for (int i = 0; i < 5; i++) {
      digitalWrite(LED1, HIGH);
      delay(100);
      digitalWrite(LED1, LOW);
      delay(100);
    }

    motor.write(0); // MOVE SERVO BACK TO 0 DEGREES
    lcd.setCursor(0, 1);
    lcd.print("Angle: 0    ");
    delay(2000);

    lcd.clear();
    return;
  }

  // HANDLE POTENTIOMETER ADJUSTMENTS
  int angle = map(analogRead(POTENTIOMETER), 0, 1023, 0, 180); // MAP THE POTENTIOMETER RANGE TO 0 -> 180. (DEGREES)
  motor.write(angle);

  if (angle == 0) {
    lcd.clear();
    digitalWrite(LED1, LOW);
    return;
  }

  // FLASH LED
  digitalWrite(LED1, HIGH);
  delay(30);
  digitalWrite(LED1, LOW);

  // UPDATE DISPLAY
  lcd.setCursor(0, 0);
  lcd.print("Manual Control ");

  lcd.setCursor(0, 1);
  lcd.print("Angle: ");
  lcd.print(angle);
  lcd.print("   ");

  delay(20);
}
