// C++ code
//

//constants
const int PIN_LED_GREEN = 13;
const int PIN_LED_RED = 12;
const int PIN_LED_YELLOW = 11;
const int PIN_BUTTON = 3;
const int MODES = 1;

//variables
int ledStateGreen = 1;
int ledStateRed = 0;
int ledStateYellow = 0;
int mode = 0;
int buttonState;
unsigned long previousMillis = 0;
int lastButtonState = LOW;
unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
unsigned long debounceDelay = 50;    // the debounce time; increase if the output flickers

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
  mode = 0;
  digitalWrite(PIN_LED_GREEN, ledStateGreen);
  delay(500);
}

void loop()
{
  unsigned long currentMillis = millis();
  int reading = digitalRead(PIN_BUTTON);
  // If the switch changed, due to noise or pressing:
  if (reading != lastButtonState) {
    // reset the debouncing timer
    lastDebounceTime = millis();
  }
  if ((millis() - lastDebounceTime) > debounceDelay) 
  {
    if (reading != buttonState) 
    {
      buttonState = reading;

      if (buttonState == LOW)
      {
        if (mode == MODES)
          mode = 0;
        else
          mode = (mode % MODES) + 1;
        previousMillis = 0;
      }
    }
  }
  
  switch (mode)
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
  // save the reading. Next time through the loop, it'll be the lastButtonState:
  lastButtonState = reading;
}