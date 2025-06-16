/*
  LiquidCrystal Library - Custom Characters

 Demonstrates how to add custom characters on an LCD  display.
 The LiquidCrystal library works with all LCD displays that are
 compatible with the  Hitachi HD44780 driver. There are many of
 them out there, and you can usually tell them by the 16-pin interface.

 This sketch prints "I <heart> Arduino!" and a little dancing man
 to the LCD.

  The circuit:
 * LCD RS pin to digital pin 12
 * LCD Enable pin to digital pin 11
 * LCD D4 pin to digital pin 5
 * LCD D5 pin to digital pin 4
 * LCD D6 pin to digital pin 3
 * LCD D7 pin to digital pin 2
 * LCD R/W pin to ground
 * 10K potentiometer:
 * ends to +5V and ground
 * wiper to LCD VO pin (pin 3)
 * 10K poterntiometer on pin A0

 created 21 Mar 2011
 by Tom Igoe
 modified 11 Nov 2013
 by Scott Fitzgerald
 modified 7 Nov 2016
 by Arturo Guadalupi

 Based on Adafruit's example at
 https://github.com/adafruit/SPI_VFD/blob/master/examples/createChar/createChar.pde

 This example code is in the public domain.
 https://docs.arduino.cc/learn/electronics/lcd-displays#custom-character

 Also useful:
 http://icontexto.com/charactercreator/

*/

// include the library code:
#include <LiquidCrystal.h>

#define POTENTIOMETER_PIN A0
#define LED 6


// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);


void setup() {
  // initialize LCD and set up the number of columns and rows:
  lcd.begin(16, 2);
  // set the cursor to the top left
  lcd.setCursor(0, 0);
  // Print a message to the lcd.
  lcd.print("LED Brightness");
  pinMode (LED, OUTPUT);
  //Serial.setTimeout(5000);
  Serial.begin(9600);
}

void lcdWrite(int ledValue)
{
  lcd.setCursor(2, 1);
  if (ledValue < 100 && ledValue > 9)
    lcd.print("0");
  else if (ledValue < 10)
    lcd.print("00");
  lcd.print(ledValue);
  lcd.print(" (");
  int percentage = map(ledValue, 0, 255, 0, 100);
  if (percentage < 100 && percentage > 9)
    lcd.print("0");
  else if (percentage < 10)
    lcd.print("00");
  lcd.print(percentage);
  lcd.print("%)");
}

void loop() {
  static int serialData = 0;
  int potData = analogRead(POTENTIOMETER_PIN);
  if (Serial.available()) {
    int tmp = Serial.parseInt();
    if (Serial.available() && tmp >=0 && tmp <= 100)
    {
      if (potData != 0)
        Serial.println("The potentiometer is not set to zero!");
      else
      {
        serialData = tmp;
        Serial.print("You entered: ");
        Serial.println(serialData);
      }
    }
  }
  int ledValue;
  if (potData == 0)
    ledValue = map(serialData,0,100,0,255);
  else
  {
    ledValue = map(potData,0,1023,0,255);
    serialData = 0;
  }
  analogWrite (LED, ledValue);
  lcdWrite(ledValue);
  delay(100);
}