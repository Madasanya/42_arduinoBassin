// C++ code
//
// TODO
//  - handle millis() overflow
//  - struct for LEDs

// enums
enum blinkingMode{
  PARALLEL_BLINK = 1,
  ALTERNATE_BLINK = 2,
  ASYN_DURATION_BLINK = 3
};

// constants
const int LED_PIN_GREEN = 13;
const int LED_PIN_RED = 12;
const int LED_PIN_YELLOW = 11;
const int BUTTON_PIN = 3;
const int MODE_AMOUNT = 3;
const unsigned long DEBOUNCE_DELAY = 50;    // the debounce time; increase if the output flickers

//variables
int mode = 0;
unsigned long currentMillis = 0;
unsigned long modeStartMillis = 0;
int buttonState;
int lastButtonState = LOW;
unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled

void blink (const int pin, unsigned long blinkStart, unsigned long blinkDuration, unsigned long cycleDuration, unsigned long modeStart)
{
  unsigned long currentCycleMillis = (currentMillis - modeStart) % cycleDuration;
  if ((currentCycleMillis >= blinkStart) && (currentCycleMillis < blinkStart + blinkDuration))
    digitalWrite(pin, HIGH);
  else
    digitalWrite(pin, LOW);
}

void setup()
{
  pinMode(LED_PIN_GREEN, OUTPUT);
  pinMode(LED_PIN_RED, OUTPUT);
  pinMode(LED_PIN_YELLOW, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  digitalWrite(LED_PIN_GREEN, HIGH);
  delay(500);
}

void loop()
{
  currentMillis = millis();
  int reading = digitalRead(BUTTON_PIN);
  // If the switch changed, due to noise or pressing:
  if (reading != lastButtonState)
  {
    // reset the debouncing timer
    lastDebounceTime = millis();
  }
  if ((currentMillis - lastDebounceTime) > DEBOUNCE_DELAY) 
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
        modeStartMillis = currentMillis;
      }
    }
  }
  
  switch (mode)
  {
    case PARALLEL_BLINK:
      digitalWrite(LED_PIN_GREEN, LOW);
      blink(LED_PIN_RED, 0, 100, 1000, modeStartMillis);
      blink(LED_PIN_YELLOW, 0, 100, 1000, modeStartMillis);
      break;
    case ALTERNATE_BLINK:
      digitalWrite(LED_PIN_GREEN, LOW);
      blink(LED_PIN_RED, 1000, 100, 2000, modeStartMillis);
      blink(LED_PIN_YELLOW, 0, 100, 2000, modeStartMillis);
      break;
    case ASYN_DURATION_BLINK:
      digitalWrite(LED_PIN_GREEN, LOW);
      blink(LED_PIN_RED, 0, 100, 500, modeStartMillis);
      blink(LED_PIN_YELLOW, 0, 100, 2000, modeStartMillis);
      break;
    default:
      digitalWrite(LED_PIN_GREEN, HIGH);
      digitalWrite(LED_PIN_RED, LOW);
      digitalWrite(LED_PIN_YELLOW, LOW); 
  }
  // save the reading. Next time through the loop, it'll be the lastButtonState:
  lastButtonState = reading;
}