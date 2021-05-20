//optimus watchin us
#define trigPin 12
#define echoPin 11 
#define MAX_DISTANCE 200 // max sensor distance is rated at 400-500cm
// define timeOut according to the max range; timeOut  = 2*MAX_DISTANCE / 100 / 340 * 1000000 = MAX_DISTANCE*58.8
float timeOut = MAX_DISTANCE * 60;

int soundVelocity = 340; // define speed of sound = 340m/s

void setup() {
  // pins and serial connection
  pinMode(trigPin, OUTPUT); // trigPin is output
  pinMode(echoPin, INPUT);  // echoPin is input from ultrasound bounce
  Serial.begin(9600);  // open serial monitor -- view ping results what optimus sees

}

void loop() {
  // int main void 
  delay(100);  /* // Wait 100ms between pings (about 20 pings/sec). 29ms should be the
shortest delay between pings. */
  Serial.print('Ping: ');
  Serial.print(getSonar());  // Send ping, get distance in cm and print result (0 = outside set distance range)
  Serial.println('cm')
}

float getSonar() {
  unsigned long pingTime;
  float distance;
  digitalWrite(trigPin, HIGH; // make trigPin output high level for 10 µs
}
