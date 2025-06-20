#include <Servo.h>

#define SERVO 9

const int ldrLeft  = A0;
const int ldrMid   = A1;
const int ldrRight = A2;

Servo servo;

const int threshold = 50;
const int numSamples = 10;

int servoAngle = 90;

void setup() {
  // put your setup code here, to run once:
  servo.attach(SERVO);
  servo.write(servoAngle);  
  Serial.begin(9600);
}

int getAverage(int pin) {
  long sum = 0;
  for (int i = 0; i < numSamples; i++) {
    sum += analogRead(pin);
    delay(2);
  }
  return sum / numSamples;
}

void loop() {
  // put your main code here, to run repeatedly:
  int leftVal  = getAverage(ldrLeft);
  int midVal   = getAverage(ldrMid);
  int rightVal = getAverage(ldrRight);
  int diff = leftVal - rightVal; 
  Serial.print("Left: ");
  Serial.print(leftVal);
  Serial.print("   Right: ");
  Serial.print(rightVal);
  Serial.print("   Middle: ");
  Serial.print(midVal);
  Serial.print("   Diff: ");
  Serial.println(diff);
  if (abs(diff) > threshold) {
    // Berechne neuen Winkel, begrenzt auf 0-180
    servoAngle = map(diff, -600, 600, 0, 180);
    servoAngle = constrain(servoAngle, 0, 180);
    servo.write(servoAngle);
  }
  delay(500);
}
