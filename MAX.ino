#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

// SETUP THE LCD DISPLAY (CREATE NEW INSTANCE)
LiquidCrystal_I2C lcd(0x27,16,2);

// DEFINE PINS TO USE AS VARIABLES
const int buttonPin = 2;

const int trigPin = 7;
const int echoPin = 6;

const int potPin = A0;

Servo gateServo;
const int servoPin = 9;

// DEFINE SERVO POSITIONS
int gateClosed = 0; // CLOSED POSITION
int gateOpen = 90;  // OPEN POSITION

// FUNCTION TO CALCULATE THE DISTANCE
long getDistance()
{
  digitalWrite(trigPin, LOW); // RESET
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH); // TRIGGER
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH); // DURATION OF "PING"
  long distance = duration * 0.034 / 2; // HALF PING (FORWARDS AND BACKWARDS)

  return distance;
}

// DEFINE FUNCTION THAT WILL MANAGE ANY WRITING TO LCD SCREEN
void lcdMessage(String line1, String line2)
{
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(line1);
  lcd.setCursor(0,1);
  lcd.print(line2);
}

// SETUP PINS FROM VARS, SETUP SERVO, INIT LCD
void setup()
{
  Serial.begin(9600);

  pinMode(buttonPin, INPUT_PULLUP);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  gateServo.attach(servoPin);
  gateServo.write(gateClosed);

  lcd.init();
  lcd.backlight();

  lcdMessage("Barrier Ready", "Waiting Car");
}

// LOOP
void loop()
{
  long distance = getDistance(); // RETURNS DISTANCE FROM ULTRASONIC SENSOR

  int potValue = analogRead(potPin); // POTENTIOMETER READING FROM PIN A0
  int threshold = map(potValue, 0, 1023, 5, 30); // CONVERTS VALUE FROM POTENTIOMETER TO VALUES 5cm TO 30cm

  
  // PRINT THE DISTANCE AND THRESHOLD IN SERIAL MONITOR
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.print(" cm | Threshold: ");
  Serial.print(threshold);
  Serial.println(" cm");

  // AWAIT A CAR TO ARRIVE WITHIN THE THRESHOLD
  if(distance < threshold)
  {
    lcdMessage("Car Detected","Press Button");

    // WAIT FOR A BUTTON PRESS WHILST CAR IS PRESENT
    while(digitalRead(buttonPin) == LOW)
    {
      delay(50);
    }

    lcdMessage("Opening Gate","");

    // OPEN THE GATE
    gateServo.write(gateOpen);
    delay(1500);

    lcdMessage("Car Passing","");

    // WAIT UNTIL THE CAR HAS PASSED THE BARRIER
    while(getDistance() < threshold)
    {
      delay(100);
    }

    // DELAY FOR THE CARS TO FULLY PASS BARRIER
    delay(3000);

    lcdMessage("Closing Gate","");

    // CLOSE THE GATE
    gateServo.write(gateClosed);
    delay(2000);

    lcdMessage("Barrier Ready","Waiting Car");
  }

  delay(100);
}
