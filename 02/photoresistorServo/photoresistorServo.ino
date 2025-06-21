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
int servo2Angle = 90;

int ldrLeftSamples[numSamples];
int ldrMidSamples[numSamples];
int ldrRightSamples[numSamples];

void setup() {
  // put your setup code here, to run once:
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
  // put your main code here, to run repeatedly:
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
  Serial.print(diff1);
  Serial.print("   Diff2: ");
  Serial.println(diff2);
  if (abs(diff1) > threshold) {
    // Berechne neuen Winkel, begrenzt auf 0-180
    servo1Angle = map(diff1, -600, 600, 0, 180);
    servo1Angle = constrain(servo1Angle, 0, 180);
    servo1.write(servo1Angle);
  }
  if (abs(diff2) > threshold) {
    // Berechne neuen Winkel, begrenzt auf 0-180
    servo2Angle = map(diff2, -600, 600, 0, 180);
    servo2Angle = constrain(servo2Angle, 0, 180);
    servo2.write(servo2Angle);
  }
  delay(500);
}
