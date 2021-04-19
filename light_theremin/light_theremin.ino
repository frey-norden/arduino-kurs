  // Light Theremin 
  // Project 06

int sensorvValue;
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

  digitalWrite(ledPin, LOW);
}

void loop() {
  int sensorValue = analogRead(A0);
  int pitch = map(sensorValue, sensorLow, sensorHigh, 50, 4000);

}
