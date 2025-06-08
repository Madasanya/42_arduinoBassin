// C++ code
//

//constants
const int PIN_LED_GREEN = 13;
const int PIN_LED_RED = 12;
const int PIN_LED_YELLOW = 11;
const int PIN_BUTTON = 3;
const int CASES =1;

//variables
int buttonState = 0;
int ledStateGreen = HIGH;
int ledStateRed = LOW;
int ledStateYellow = LOW;
unsigned long previousMillis = 0;

// if the LED is off turn it on and vice-versa:
int revLEDState(int *ledState)
{
  if (*ledState == LOW) {
    *ledState = HIGH;
  } else {
    *ledState = LOW;
  }
  return *ledState;
}  

void setup()
{
  pinMode(PIN_LED_GREEN, OUTPUT);
  pinMode(PIN_LED_RED, OUTPUT);
  pinMode(PIN_LED_YELLOW, OUTPUT);
  pinMode(PIN_BUTTON, INPUT_PULLUP);
  digitalWrite(PIN_LED_GREEN, ledStateGreen);
  delay(500);
}

void loop()
{
  unsigned long currentMillis = millis();
  if (digitalRead(PIN_BUTTON) == 0) 
  {
    if (buttonState == CASES)
      buttonState = 0;
    else
      buttonState = (buttonState % CASES) + 1;
    previousMillis = 0;
  }
  switch (buttonState)
  {
    case 1:
      ledStateGreen = LOW;
      digitalWrite(PIN_LED_GREEN, ledStateGreen);
      if (currentMillis - previousMillis >= 500) 
      {
        // save the last time you blinked the LED
        previousMillis = currentMillis;
        digitalWrite(PIN_LED_RED, revLEDState(&ledStateRed));
        digitalWrite(PIN_LED_YELLOW, revLEDState(&ledStateYellow));
      }
      break;
    //case 2:
    //  digitalWrite(PIN_LED_GREEN, revLEDState(&ledStateGreen));
    //  digitalWrite(PIN_LED_RED, HIGH);
    //  digitalWrite(PIN_LED_YELLOW, LOW);
    //  delay(1000); // Wait for 1000 millisecond(s)
    //  digitalWrite(PIN_LED_RED, LOW);
    //  digitalWrite(PIN_LED_YELLOW, HIGH);
    //  delay(1000); // Wait for 1000 millisecond(s)
    //  break;
    //case 3:
    //  digitalWrite(PIN_LED_GREEN, LOW);
    //  digitalWrite(PIN_LED_RED, HIGH);
    //  digitalWrite(PIN_LED_YELLOW, HIGH); 
    //  break;
    default:
      digitalWrite(PIN_LED_GREEN, HIGH);
      digitalWrite(PIN_LED_RED, LOW);
      digitalWrite(PIN_LED_YELLOW, LOW); 
  }
}
