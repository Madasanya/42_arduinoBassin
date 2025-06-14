// C++ code
//
#define POTENTIOMETER_PIN A0
#define LED 11
int sensorValue = 0;

void setup() //Hier beginnt das Setup.
{
	pinMode (LED, OUTPUT);
  Serial.begin(9600);
}
void loop()
{
  int data = analogRead(POTENTIOMETER_PIN);
  analogWrite (LED, map(data,0,1023,0,255));
  int percentage = map(data, 0, 1023, 0, 100);
  Serial.print("Potentiometer at ");
  Serial.print(percentage);
  Serial.println("%");
  delay(1000);
}