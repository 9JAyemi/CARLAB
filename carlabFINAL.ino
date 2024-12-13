#include "pitches.h"
int green = 3;
int yellow = 2;
int red = 4;

 // Notes and durations
int melody[] = { 262, 262, 392, 392, 440, 440, 392, // Twinkle, Twinkle 
349, 349, 330, 330, 294, 294, 262, // Little Star 
392, 392, 349, 349, 330, 330, 294, // How I wonder 
392, 392, 349, 349, 330, 330, 294 // What you are 
};

int noteDurations2[] = { 500, 500, 500, 500, 500, 500, 1000, 
  500, 500, 500, 500, 500, 500, 1000, 500, 500, 500, 500, 500,
   500, 1000, 500, 500, 500, 500, 500, 500, 1000 
   }; 
// notes in the melody:

int melody1[] = {


  NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4

};


// note durations: 4 = quarter note, 8 = eighth note, etc.:

int noteDurations[] = {


  4, 8, 8, 4, 4, 4, 4, 4

};


void setup() {
Serial.begin(9600); //Initializie Serial Communication
pinMode(green, INPUT);
pinMode(yellow, INPUT);
pinMode(red, INPUT);

}


void loop() {
  int greenstate = digitalRead(green);
  int yellowstate = digitalRead(yellow);
  int redstate = digitalRead(red);
  bool playyellow = false;
  bool playred = false;
  bool playgreen = false;

    if (greenstate == HIGH){
      playgreen = true;
      playred = false;
      playyellow = false;
    }

    if (redstate == HIGH) {
      playred = true;
      playyellow = false;
      playgreen = false;
    }

    if (yellowstate == HIGH){
      playyellow = true;
      playred = false;
      playgreen = false; 
    }

    while(playgreen){
   for (int thisNote = 0; thisNote < 8; thisNote++) {


    // to calculate the note duration, take one second divided by the note type.


    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.


    int noteDuration = 1000 / noteDurations[thisNote];


    tone(9, melody1[thisNote], noteDuration);


    // to distinguish the notes, set a minimum time between them.


    // the note's duration + 30% seems to work well:


    int pauseBetweenNotes = noteDuration * 1.30;


    delay(pauseBetweenNotes);

     if (digitalRead(red) == HIGH) {
      playred = true;
      playyellow = false;
      playgreen = false;
      break;
    }

     if (digitalRead(yellow) == HIGH){
      playyellow = true;
      playred = false;
      playgreen = false; 
      break;
    }
  }
    }

    while(playred) {
        // stop the tone playing:
        noTone(9);
      
      if (digitalRead(green) == HIGH){
      playgreen = true;
      playred = false;
      playyellow = false;
    }

    if (digitalRead(yellow) == HIGH){
      playyellow = true;
      playred = false;
      playgreen = false; 
    }

    }
  

    while(playyellow) {
    // Loop through the notes of the melody 
    for (int i = 0; i < sizeof(melody) / sizeof(melody[0]); i++) { 
      int note = melody[i]; int duration = noteDurations2[i]; tone(9, note, duration); // Play the note 
      delay(duration * 1.3); // Wait for note to finish with a slight pause 
      
      if (digitalRead(green) == HIGH){
      playgreen = true;
      playred = false;
      playyellow = false;
      break;
    }

    if (digitalRead(red) == HIGH) {
      playred = true;
      playyellow = false;
      playgreen = false;
      break;
    }
      }

   
    }
  }

  


