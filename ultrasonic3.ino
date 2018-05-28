#include <NewPing.h>

// ---------------------------------------------------------------------------
// Example NewPing library sketch that does a ping about 20 times per second.
// ---------------------------------------------------------------------------

//3 depan, 2 kanan, 1 kiri
#define TRIGGER_PIN_1  2  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN_1     3  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define TRIGGER_PIN_2  6  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN_2     7  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define TRIGGER_PIN_3  4  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN_3     5  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 200 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.
int a, b, c;

int dir1PinA = 13;
int dir2PinA = 12;
int speedPinA = 10;

int dir1PinB = 11;
int dir2PinB = 8;
int speedPinB = 9;
int speed;

int status;

void setup() {
  Serial.begin(115200); // Open serial monitor at 115200 baud to see ping results.
  pinMode (dir1PinA, OUTPUT);
  pinMode (dir2PinA, OUTPUT);
  pinMode (speedPinA, OUTPUT);
  pinMode (dir1PinB, OUTPUT);
  pinMode (dir2PinB, OUTPUT);
  pinMode (speedPinB, OUTPUT);
  speed = 255;
}

int ultrablue(int a, int b){
  NewPing sonar(a, b, MAX_DISTANCE); // NewPing setup of pins and maximum distance.
  delay(50);                     // Wait 50ms between pings (about 20 pings/sec). 29ms should be the shortest delay between pings.
  return(sonar.ping_cm());
}

void printValue(int a, int b){
  Serial.print("Ping ");
  Serial.print(b);
  Serial.print(" :");
  Serial.println(a); // Send ping, get distance in cm and print result (0 = outside set distance range)
}

void loop() {
  a = ultrablue(TRIGGER_PIN_1, ECHO_PIN_1);
  printValue(a, 1);
  delay(50);
  b = ultrablue(TRIGGER_PIN_2, ECHO_PIN_2);
  printValue(b, 2);
  delay(50);
  c = ultrablue(TRIGGER_PIN_3, ECHO_PIN_3);
  printValue(c, 3);
  delay(1000);
  switch (status){
    case 1:
      maju();
      if (c <= 10) {
        if (b <=10 && a <= 10) {
          status = 2;
          break;    
        } else if (b <= 10) {
          kiri();
          delay(250);
          break;
        } else if (a <= 10) {
          kanan();
          delay(250);
          break;
        }
      } 
    case 2:
      mundur();
      if (b >= 10) {
        kanan();
        status = 1;
        break;
      } else if (a >= 10) {
        kiri();
        status = 1;
        break;
      }
  }   
}

void maju() {
  analogWrite (speedPinA, speed);
  digitalWrite (dir1PinA , LOW);
  digitalWrite (dir2PinA, HIGH);
  analogWrite (speedPinB, speed);
  digitalWrite (dir1PinB , LOW);
  digitalWrite (dir2PinB, HIGH);
}

void mundur() {
  analogWrite (speedPinA, speed);
  digitalWrite (dir1PinA , HIGH);
  digitalWrite (dir2PinA, LOW);
  analogWrite (speedPinB, speed);
  digitalWrite (dir1PinB , HIGH);
  digitalWrite (dir2PinB, LOW);
}

void kiri() {
  analogWrite (speedPinA, speed);
  digitalWrite (dir1PinA , LOW);
  digitalWrite (dir2PinA, HIGH);
  analogWrite (speedPinB, speed);
  digitalWrite (dir1PinB , HIGH);
  digitalWrite (dir2PinB, LOW);
}

void kanan() {
  analogWrite (speedPinA, speed);
  digitalWrite (dir1PinA , HIGH);
  digitalWrite (dir2PinA, LOW);
  analogWrite (speedPinB, speed);
  digitalWrite (dir1PinB , LOW);
  digitalWrite (dir2PinB, HIGH);
}

void berhenti() {
  analogWrite (speedPinA, 0);
  digitalWrite (dir1PinA , LOW);
  digitalWrite (dir2PinA, LOW);
  analogWrite (speedPinB, 0);
  digitalWrite (dir1PinB , LOW);
  digitalWrite (dir2PinB, LOW);
}
