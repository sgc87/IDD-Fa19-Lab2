/*
  Modified by Samuel Choi
  Editor: Samuel Choi
  Cornell ID: sgc87
  Due Date: Sept 16, 2019
  ***********************
  Analog Input
  
  created by David Cuartielles
  last modified by creator 30 Aug 2011
  By Tom Igoe

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/AnalogInput
*/
// include the library code:
#include <LiquidCrystal.h>

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

int sensorPin = A0;    // select the input pin for the potentiometer
float sensorValue = 0;  // variable to store the value coming from the sensor

void setup() {
  lcd.begin(16, 2); //initialize the lcd
}

void loop() {
  // read the value from the sensor:
  sensorValue = analogRead(sensorPin);
  lcd.begin(16, 2); //reposition every refresh
  lcd.print(sensorValue); //print the analog value
  delay(500); //wait for about a half second before refreshing
}
