#include <Servo.h>

const int ldrLeftPin  = A0;
const int ldrMidPin   = A1;
const int ldrRightPin = A2;
const int servo1Pin = 9;
const int servo2Pin = 6;

Servo servo1;
Servo servo2;

const int threshold = 50;
const int numSamples = 10;

int servo1Angle = 90;
int servo2Angle = 0;

int ldrLeftSamples[numSamples];
int ldrMidSamples[numSamples];
int ldrRightSamples[numSamples];

void setup() {
  servo1.attach(servo1Pin);
  servo2.attach(servo2Pin);
  servo1.write(servo1Angle);
  servo2.write(servo2Angle); 
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
  int leftVal  = getAverage(ldrLeftPin);
  int midVal   = getAverage(ldrMidPin);
  int rightVal = getAverage(ldrRightPin);
  int diff1 = leftVal - rightVal; 
  int diff2 = midVal - ((leftVal + rightVal) / 2);
  Serial.print("Left: ");
  Serial.print(leftVal);
  Serial.print("   Right: ");
  Serial.print(rightVal);
  Serial.print("   Middle: ");
  Serial.print(midVal);
  Serial.print("   Diff1: ");
  Serial.println(diff1);
  if (abs(diff1) > threshold) {
    // Calculate angle between 30 - 150 considering LDR values between 0 and 650 
    servo1Angle = map(diff1, 0, 650, 30, 15 0);
    servo1Angle = constrain(servo1Angle, 30, 150);
    servo1.write(servo1Angle);
  }
  if (abs(midVal) > threshold) {
    // Calculate angle between 0 - 180 considering LDR values between 0 and 650 
    servo2Angle = map(midVal, 0, 650, 0, 180);
    servo2Angle = constrain(servo2Angle, 0, 180);
    servo2.write(servo2Angle);
  }
  // servo1.write(90);
  // servo2.write(0);
  delay(500);
}
