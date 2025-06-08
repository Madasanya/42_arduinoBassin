// C++ code
//

//constants
const int PIN_LED_GREEN = 13;
const int PIN_LED_RED = 12;
const int PIN_LED_YELLOW = 11;
const int PIN_BUTTON = 3;
const int MODES = 3;
const unsigned long debounceDelay = 50;    // the debounce time; increase if the output flickers

//variables
int ledStateRed = LOW;
int ledStateYellow = LOW;
int mode = 0;
unsigned long currentMillis = 0;
unsigned long previousMillisRed = 0;
unsigned long previousMillisYellow = 0;
int ledBlinkStateRed = 0;
int ledBlinkStateYellow = 0;
int buttonState;
int lastButtonState = LOW;
unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled


void blink (const int pin, unsigned long delay, unsigned long duration, unsigned long pause, int *ledState, unsigned long * previousMillis)
{
  // delay = delay*1000;
  // duration = duration *1000;
  // pause = pause *1000;
  currentMillis = millis();
  switch (*ledState)
  {
    case 0: // TODO: Use macros (enums)
    	*previousMillis = currentMillis;
    	digitalWrite(pin, LOW);
    	*ledState = 1; 
    	break;
    case 1:
    	if (currentMillis - *previousMillis > delay) 
        {
          digitalWrite(pin, HIGH);
          *ledState = 2;
          *previousMillis = currentMillis;
        }
    	break;
    case 2:
    	if (currentMillis - *previousMillis > duration) 
        {
          digitalWrite(pin, LOW);
          *ledState = 3;
          *previousMillis = currentMillis;
        }
    	break;
    default:
    	if (currentMillis - *previousMillis > pause) 
      {
        digitalWrite(pin, LOW);
        *ledState = 1;
        *previousMillis = currentMillis;
      }
  }
}

void setup()
{
  pinMode(PIN_LED_GREEN, OUTPUT);
  pinMode(PIN_LED_RED, OUTPUT);
  pinMode(PIN_LED_YELLOW, OUTPUT);
  pinMode(PIN_BUTTON, INPUT_PULLUP);
  mode = 0;
  digitalWrite(PIN_LED_GREEN, HIGH);
  delay(500);
}

void loop()
{
  currentMillis = millis();
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
        previousMillisRed = currentMillis;
        previousMillisYellow = currentMillis;
        ledBlinkStateRed = 0;
        ledBlinkStateYellow = 0;
      }
    }
  }
  
  switch (mode)
  {
    case 1: //TODO: structure for blink
      digitalWrite(PIN_LED_GREEN, LOW);
      blink(PIN_LED_RED, 0, 500, 500, &ledBlinkStateRed, &previousMillisRed);
      blink(PIN_LED_YELLOW, 0, 500, 500, &ledBlinkStateYellow, &previousMillisYellow);
      break;
    case 2:
      digitalWrite(PIN_LED_GREEN, LOW);
      blink(PIN_LED_RED, 0, 100, 1900, &ledBlinkStateRed, &previousMillisRed);
      blink(PIN_LED_YELLOW, 1000, 100, 900, &ledBlinkStateYellow, &previousMillisYellow);
      break;
    case 3:
      digitalWrite(PIN_LED_GREEN, LOW);
      blink(PIN_LED_RED, 0, 100, 400, &ledBlinkStateRed, &previousMillisRed);
      blink(PIN_LED_YELLOW, 0, 100, 1900, &ledBlinkStateYellow, &previousMillisYellow);
      break;
    default:
      digitalWrite(PIN_LED_GREEN, HIGH);
      digitalWrite(PIN_LED_RED, LOW);
      digitalWrite(PIN_LED_YELLOW, LOW); 
  }
  // save the reading. Next time through the loop, it'll be the lastButtonState:
  lastButtonState = reading;
}