// mobile code life
// digital hourglass - project 08 

const int switchPin = 8;

unsigned long previousTime = 0; 
int switchState = 0;

int led = 2;
long interval = 600000;


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
  if(currentTime - previousTime > interval)

}
