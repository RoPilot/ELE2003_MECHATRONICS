// DEFINE PACKAGES
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// CREATE NEW LCD INSTANCE, 16X2
LiquidCrystal_I2C lcd(0x27, 16, 2);

// DEFINE PINS, EASY FOR PROTOTYPING
int Photoresistor = A1;
int POTENTIOMETER = A0;
int Rled = 9;
int Wled = 10;

// INIT SETUP
void setup() {

  pinMode(Rled, OUTPUT);
  pinMode(Wled, OUTPUT);

  Serial.begin(9600);

  lcd.init();          // INITIALISE LCD
  lcd.backlight();     // TOGGLE BACKLIGHT
}

// CODE LOOP
void loop() {

  // READ THE PHOTORESISTOR VALUE, AND THE THRESHOLD,
  // WHICH IS DEFINED BY THE POTENTIOMETER.
  int Currentlight = analogRead(Photoresistor);
  int lightthreshold = analogRead(POTENTIOMETER);

  // PRINT LIGHT AND THRESHOLD TO SERIAL MONITOR
  Serial.print("Light = ");
  Serial.print(Currentlight);
  Serial.print(" | Threshold = ");
  Serial.println(lightthreshold);

  // IF THE LIGHT LEVEL IS LESS THAN THE LIGHT THRESHOLD THEN,
  // TURN ON THE LIGHTS, ELSE, TURN THEM OFF
  if (Currentlight < lightthreshold) {
    digitalWrite(Rled, HIGH);
    digitalWrite(Wled, HIGH);
  } 
  else {
    digitalWrite(Rled, LOW);
    digitalWrite(Wled, LOW);
  }

  // DISPLAY DATA TO THE LCD DISPLAY
  lcd.setCursor(0,0);
  lcd.print("Threshold:");

  // MOVE CURSOR TO SECOND ROW, THEN WRITE
  lcd.setCursor(0,1);
  lcd.print(lightthreshold);
  lcd.print("    ");   // clears leftover digits

  delay(200);
}
