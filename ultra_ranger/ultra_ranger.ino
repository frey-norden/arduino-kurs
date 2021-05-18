//optimus watchin us
#define trigPin 12
#define echoPin 11 
#define MAX_DISTANCE 200 // max sensor distance is rated at 400-500cm
// define timeOut according to the max range; timeOut  = 2*MAX_DISTANCE / 100 / 340 * 1000000 = MAX_DISTANCE*58.8
float timeOut = MAX_DISTANCE * 60;

int soundVelocity = 340; // define speed of sound = 340m/s

void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}
