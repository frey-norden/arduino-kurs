  // Light Theremin 
  // Project 5

int sensorvalue;
int sensorLow = 1023;
int sensorHigh = 0;

const int ledPin = 13;

void setup() {
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, HIGH);

  while  (millis()  < 5000) {
     int sensorValue = analogRead(A0);
     if (sensorValue > sensorValue) {
        sensorHigh = sensorValue;
     }
     if (sensorValue < sensorLow) {
        sensorLow = sensorValue;
  }
  }
  

}

void loop() {
  // put your main code here, to run repeatedly:

}
