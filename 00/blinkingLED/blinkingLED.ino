// C++ code
//

typedef struct led_s{
  const int PIN;
  unsigned long previousMillis;
  int ledBlinkState;

} led_t;

enum blinkStage{
  BLINK_INIT,
  BLINK_DELAY,
  BLINK_DURATION,
  BLINK_PAUSE
};

enum assignmentMode{
  MANDATORY = 1,
  BONUS1 = 2,
  BONUS2 = 3
};

//constants
const int LED_PIN_GREEN = 13;
const int LED_PIN_RED = 12;
const int LED_PIN_YELLOW = 11;
const int BUTTON_PIN = 3;
const int MODE_AMOUNT = 3;
const unsigned long DEBOUNCE_DELAY = 50;    // the debounce time; increase if the output flickers

//variables
int mode = 0;
unsigned long currentMillis = 0;
unsigned long previousMillisRed = 0;
unsigned long previousMillisYellow = 0;
int ledBlinkStateRed = 0;
int ledBlinkStateYellow = 0;
int buttonState;
int lastButtonState = LOW;
unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
led_t green = {LED_PIN_GREEN, 0, 0};
led_t red = {LED_PIN_RED, 0, 0};
led_t yellow = {LED_PIN_YELLOW, 0, 0};


void blink (const int pin, unsigned long delay, unsigned long duration, unsigned long pause, int *ledState, unsigned long * previousMillis)
{
  currentMillis = millis();
  switch (*ledState)
  {
    case BLINK_INIT:
    	*previousMillis = currentMillis;
    	digitalWrite(pin, LOW);
    	*ledState = 1; 
    	break;
    case BLINK_DELAY:
    	if (currentMillis - *previousMillis > delay) 
        {
          digitalWrite(pin, HIGH);
          *ledState = 2;
          *previousMillis = currentMillis;
        }
    	break;
    case BLINK_DURATION:
    	if (currentMillis - *previousMillis > duration) 
        {
          digitalWrite(pin, LOW);
          *ledState = 3;
          *previousMillis = currentMillis;
        }
    	break;
    default: // Pause
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
  pinMode(LED_PIN_GREEN, OUTPUT);
  pinMode(LED_PIN_RED, OUTPUT);
  pinMode(LED_PIN_YELLOW, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  mode = 0;
  digitalWrite(LED_PIN_GREEN, HIGH);
  delay(500);
}

void loop()
{
  currentMillis = millis();
  int reading = digitalRead(BUTTON_PIN);
  // If the switch changed, due to noise or pressing:
  if (reading != lastButtonState) {
    // reset the debouncing timer
    lastDebounceTime = millis();
  }
  if ((millis() - lastDebounceTime) > DEBOUNCE_DELAY) 
  {
    if (reading != buttonState) 
    {
      buttonState = reading;

      if (buttonState == LOW)
      {
        if (mode == MODE_AMOUNT)
          mode = 0;
        else
          mode = (mode % MODE_AMOUNT) + 1;
        previousMillisRed = currentMillis;
        previousMillisYellow = currentMillis;
        ledBlinkStateRed = 0;
        ledBlinkStateYellow = 0;
      }
    }
  }
  
  switch (mode)
  {
    case MANDATORY: //TODO: structure for blink
      digitalWrite(LED_PIN_GREEN, LOW);
      blink(LED_PIN_RED, 0, 500, 500, &ledBlinkStateRed, &previousMillisRed);
      blink(LED_PIN_YELLOW, 0, 500, 500, &ledBlinkStateYellow, &previousMillisYellow);
      break;
    case BONUS1:
      digitalWrite(LED_PIN_GREEN, LOW);
      blink(LED_PIN_RED, 0, 100, 1900, &ledBlinkStateRed, &previousMillisRed);
      blink(LED_PIN_YELLOW, 1000, 100, 900, &ledBlinkStateYellow, &previousMillisYellow);
      break;
    case BONUS2:
      digitalWrite(LED_PIN_GREEN, LOW);
      blink(LED_PIN_RED, 0, 100, 400, &ledBlinkStateRed, &previousMillisRed);
      blink(LED_PIN_YELLOW, 0, 100, 1900, &ledBlinkStateYellow, &previousMillisYellow);
      break;
    default:
      digitalWrite(LED_PIN_GREEN, HIGH);
      digitalWrite(LED_PIN_RED, LOW);
      digitalWrite(LED_PIN_YELLOW, LOW); 
  }
  // save the reading. Next time through the loop, it'll be the lastButtonState:
  lastButtonState = reading;
}