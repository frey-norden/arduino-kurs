// mobile code life
// digital hourglass - project 08 

const int switchPin = 8;

unsigned long previousTime = 0; 
int switchState = 0;

int led = 2;
long interval = 600000; // 10 mins in millis 10 * 60  secs


void setup() {
  // setup leds and pins
  for(int x=2; x<8;x++){
    pinMode(x, OUTPUT); // it's gonna go from  2 to 8 first arg x is pin
  }
  
  pinMode(switchPin, INPUT);
}

void loop() {
  // time for the loop int main void arg loopy loop
  unsigned  long currentTime = millis();
  if(currentTime - previousTime > interval); {
    previousTime = currentTime;
    digitalWrite(led, HIGH);  // lights the pin
    led++;

    if(led ==  7){
      // something happens at end of hour -- lightshow doors pink floyd?
    }
  }
  switchState = digitalRead(switchPin);
  if(switchState != prevSwitchState){
    for(int x=2;x<8;x++){
      digitalWrite(x, LOW);
    }

    led = 2;
    previousTime = currentTime;
  }
  
  prevSwitchState = switchState;
}
