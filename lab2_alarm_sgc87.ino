/* Rotary encoder test code
   Modified from http://www.circuitsathome.com/mcu/programming/reading-rotary-encoder-on-arduino by Oleg
   Latest mod by Jessica Faruque 7/17/2013
*/


#define ENC_A 6 //these need to be digital input pins
#define ENC_B 7
#define PUSH 10

// include the library code:
#include <LiquidCrystal.h>
#include "pitches.h"

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

// notes in the melody:
int melody[] = {
  NOTE_CS4, NOTE_B4, NOTE_CS4, NOTE_FS4, 0, \
  NOTE_D4, NOTE_CS4, NOTE_D4, NOTE_CS4, NOTE_B4, 0, \
  NOTE_D4, NOTE_CS4, NOTE_D4, NOTE_FS4, 0, 
  NOTE_B4, NOTE_A4, NOTE_B4, NOTE_A4, NOTE_GS4, NOTE_B4};
 
int noteDurations[] = {
  8, 8, 2, 2, 2, \
  8, 8, 4, 4, 2, 2, \
  8, 8, 2, 2, 2, \
  8, 8, 4, 4, 4, 4};
  

void setup()
{
  /* Setup encoder pins as inputs */
  pinMode(ENC_A, INPUT_PULLUP);
  pinMode(ENC_B, INPUT_PULLUP);
  pinMode(PUSH, INPUT_PULLUP);
  lcd.begin(16, 2); //initialize the lcd
  lcd.print("The Final");
  lcd.setCursor(0, 1);
  lcd.print("Countdown");
  lcd.setCursor(0, 0);
}

void loop()
{
  static unsigned int counter4x = 0;      //the SparkFun encoders jump by 4 states from detent to detent
  static unsigned int counter = 0;
  static unsigned int prevCounter = 0;
  int tmpdata;
  int timer;
  int pushButton = digitalRead(PUSH);
  tmpdata = read_encoder();
  if (tmpdata) {
    counter4x += tmpdata;
    counter = counter4x / 4;
    if (prevCounter != counter) {
      lcd.begin(16, 2); //reposition every refresh
      lcd.print(counter); //print the analog value
    }
    prevCounter = counter;
  }
  if (pushButton == LOW) {
    timer = counter;
    while (timer > 0) {
      --timer;
      lcd.begin(16, 2); //reposition every refresh
      lcd.print(timer); //print the analog value
      delay(1000);
      if (timer == 0) {
        // iterate over the notes of the melody:
        for (int thisNote = 0; thisNote < 22; thisNote++) {
          // to calculate the note duration, take one second divided by the note type.
          //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
          int noteDuration = 1000 / noteDurations[thisNote];
          tone(8, melody[thisNote], noteDuration);

          // to distinguish the notes, set a minimum time between them.
          // the note's duration + 30% seems to work well:
          int pauseBetweenNotes = noteDuration * 1.30;
          delay(pauseBetweenNotes);
          // stop the tone playing:
          noTone(8);
        }
      }
    }
  }
}

/* returns change in encoder state (-1,0,1) */
int read_encoder()
{
  static int enc_states[] = {
    0, -1, 1, 0, 1, 0, 0, -1, -1, 0, 0, 1, 0, 1, -1, 0
  };
  static byte ABab = 0;
  ABab *= 4;                   //shift the old values over 2 bits
  ABab = ABab % 16;    //keeps only bits 0-3
  ABab += 2 * digitalRead(ENC_A) + digitalRead(ENC_B); //adds enc_a and enc_b values to bits 1 and 0
  return ( enc_states[ABab]);


}
