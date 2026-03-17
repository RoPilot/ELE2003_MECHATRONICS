// DEFINE THE PINS
int red = 9;
int yellow = 8;
int green = 7;
int buttonPin = 2;
int rgbRed = 3;
int rgbBlue = 4;
int rgbGreen = 5;
int buzzer = 6;

// INITIAL SETUP
void setup() {
  pinMode(red, OUTPUT);
  pinMode(yellow, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(buttonPin, INPUT);
  pinMode(rgbRed, OUTPUT);
  pinMode(rgbGreen, OUTPUT);
  pinMode(rgbBlue, OUTPUT);
  pinMode(buzzer, OUTPUT);
}

// SYSTEM LOOP
void loop() {

  // "ON-STATE" GREEN ONLY... TRAFFIC FLOWS...
  digitalWrite(green, HIGH);
  digitalWrite(yellow, LOW);
  digitalWrite(red, LOW);
  digitalWrite(buzzer, LOW);
  digitalWrite(rgbRed, HIGH);   
  digitalWrite(rgbGreen, LOW);  
  digitalWrite(rgbBlue, LOW);

  // WAIT FOR A PEDESTRIAN TO PRESS BUTTON TO CROSS,
  // COMPLETE TRAFFIC LIGHT CYCLE.
  if (digitalRead(buttonPin) == HIGH) {
    delay(2000); 
    digitalWrite(green, LOW);
    digitalWrite(yellow, HIGH);
    delay(2000);
    digitalWrite(yellow, LOW);
    digitalWrite(red, HIGH);
    delay(500);
    digitalWrite(rgbRed, LOW);   
    digitalWrite(rgbGreen, HIGH);
    digitalWrite(buzzer, HIGH);
    delay(5000);
    digitalWrite(buzzer, LOW);
    digitalWrite(rgbGreen, LOW);
    digitalWrite(rgbRed, HIGH);
    delay(500);
    digitalWrite(yellow, HIGH);
    delay(3000);
    digitalWrite(red, LOW);
    digitalWrite(yellow, LOW);

    // HANDLE ANY BOUNCE ON BUTTON, "DEBOUNCE"
    while (digitalRead(buttonPin) == HIGH) {
      delay(10); 
    }
  }
}
