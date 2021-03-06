//project 4  from ultimate starter kit arduino
// color mixing lamp
// first the LED and sensor pins 

const int greenLEDPin = 9;
const int redLEDPin = 10;
const int blueLEDPin = 11;

const int redSensorPin = A0;
const int greenSensorPin = A1;
const int blueSensorPin = A2;


void setup() {
  Serial.begin(9600);

  pinMode(greenLEDPin, OUTPUT);
  pinMode(redLEDPin, OUTPUT);
  pinMode(blueLEDPin, OUTPUT);

}

void loop() {
  float redSensorValue = analogRead(redSensorPin);
  delay(5);
  float greenSensorValue = analogRead(greenSensorPin);
  delay(5);
  float blueSensorValue = analogRead(blueSensorValue);

  float redValue = redSensorValue/4;
  float greenValue = greenSensorPin/4;
  float blueValue  = blueSensorValue/4;

  
  // this is console output
  Serial.print('Mapped Sensor Values \t red: ');
  Serial.print(redValue);
  Serial.print('\t green: ');
  Serial.print(greenValue);
  Serial.print('\t  blue: ');
  Serial.print(blueValue);

  // now output through LED
  analogWrite(redLEDPin, redValue);
  analogWrite(greenLEDPin, greenValue);
  analogWrite(blueLEDPin, blueValue);

}
