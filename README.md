# Digital Timer

**Samuel Choi (sgc87)**

**Due: September 17, 2019**

Include your responses to the bold questions below. Include snippets of code that explain what you did. Deliverables are due next Tuesday. Post your lab reports as README.md pages on your GitHub, and post a link to that on your main class hub page.

## Pre-Lab
 1) Dial keypad: A dial that changes notes for the Arduino device to play through speakers. 
 2) Metronome: A light and sound based metronome that is adjustable by the dial. 
 3) 21 Questions: A game that only needs two buttons to play. May require flash memory for quesiton bank. 
 4) Stopwatch: A stopwatch only requires a button and a display. 
 5) Timer: A timer can use a dial, a button, and a display
 6) rgb: A dial can adjust RGB if the push down button is used to change states for selecting to change red, green, or blue to be able to create just about any color. 
 7) mp3 player: This would be complicated, but possible. It would require a flash memory card to be used. 
 8) rand number generaator: This would be fairly simple and only require once button and a screen. 
 9) alarm clock: This Requires just a dial and the push down button to turn the set alarm on or off. 
10) that was easy buttom: May require an SD card for the sound file, but it's pretty straight forward and fun. 

![Illustrations of Pre-Lab Ideas](https://github.com/sgc87/IDD-Fa19-Lab2/blob/master/Pre-lab%20Sketches.jpg)

## Part A. Solder your LCD panel

![Part A LCD Solder](https://github.com/sgc87/IDD-Fa19-Lab2/blob/master/LCD%20Solder.jpg)

## Part B. Writing to the LCD
 
**a. What voltage level do you need to power your display?**
The LCD display requires 5V. 

**b. What voltage level do you need to power the display backlight?**
The display backlight requires 3.3V. 
   
**c. What was one mistake you made when wiring up the display? How did you fix it?**
I wasn't getting power to the board. However, I didn't realize that the power strips at the side of the boards are cut off in the middle of the board. 

To fix it, I had to use wires to makes the bottom parts of the strip live as well. 

![Board Error](https://github.com/sgc87/IDD-Fa19-Lab2/blob/master/Board_Error.jpg)

**d. What line of code do you need to change to make it flash your name instead of "Hello World"?**
I had to change the text inbetween the quotations in the following function.  
```lcd.print("");```

```
void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("Samuel Choi");
}
```
 
**e. Include a copy of your Lowly Multimeter code in your lab write-up.**
[Multimeter Code](https://github.com/sgc87/IDD-Fa19-Lab2/blob/master/multimeter_sgc87.ino)

## Part C. Using a time-based digital sensor

[Rotary Encoder Video](https://l.facebook.com/l.php?u=https%3A%2F%2Fyoutu.be%2Foc_immYQTo8%3Ffbclid%3DIwAR1QU2X6IA-nAEVBljFnNDXLBaRemzhXAcw24lmihTY0dQrd77Vvv2nVnpA&h=AT3U13gbsLkSuN9OVYjvlSiaQfaGe-q3VRKpHFUS-lVIKvIdQMIjnP7NKvAB94j9GWbWYHtXXQvjbT8WQKYcx-3Jm4Z0uePWFEnMbGwVQAh80W3fl0veXf1Ww3hCN-GXu3u8pQ)


## Part D. Make your Arduino sing!

**a. How would you change the code to make the song play twice as fast?**
One can divide the value of noteDuration by a factor of 2 in the for loop
or
double each value in the array noteDurations
```
int noteDurations[] = {
  10,10,10,2,2,10,10,10,2,4, \
  10,10,10,2,4,10,10,10,2,4};

void setup() {
  // iterate over the notes of the melody:
  for (int thisNote = 0; thisNote < 20; thisNote++) {

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
```
 
**b. What song is playing?**
Star Wars Theme Song

## Part E. Make your own timer

**a. Make a short video showing how your timer works, and what happens when time is up!**
I made a timer where the user sets the time, and then when the button is pressed, the timer ticks to zero. 
Once zero is reached, The Final Countdown, the song, is played. 
[The Final Countdown!](https://www.youtube.com/watch?v=4EsD4VwtIyg&feature=share&fbclid=IwAR22yKTyRz1F26sq5BCkoCNKnhx7o9P6lWNpHR57-5ZHqzr3bFMPA9-uE0M)

The following is my code used in the video. I have also uploaded it in my lab 2 repository. 
```
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
```

**b. Post a link to the completed lab report your class hub GitHub repo.**
