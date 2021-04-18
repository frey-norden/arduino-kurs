#include <Servo.h>
Servo myServo;

int const potPin = A0;
int potVal;
int angle;

void setup() {
  // now setup
  myServo.attach(9);

  Serial.begin(9600);

}

void loop() {
  // 
  potVal = analogRead(potPin);
  Serial.print(', angle');
  Serial.println(angle);

  myServo.write(angle);
  delay(15);
}
