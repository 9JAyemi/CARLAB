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

  NOTE_E5, NOTE_E5, NOTE_E5,  // Jingle bells
  NOTE_E5, NOTE_E5, NOTE_E5,  // Jingle bells
  NOTE_E5, NOTE_G5, NOTE_C5, NOTE_D5, NOTE_E5, // Jingle all the way
  NOTE_F5, NOTE_F5, NOTE_F5, NOTE_F5,          // Oh what fun it is to ride
  NOTE_F5, NOTE_E5, NOTE_E5, NOTE_E5, NOTE_E5, // In a one-horse open sleigh
  NOTE_E5, NOTE_D5, NOTE_D5, NOTE_E5, NOTE_D5, // Hey!
  NOTE_G5

};


// note durations: 4 = quarter note, 8 = eighth note, etc.:

int noteDurations[] = {
  8, 8, 4,  // Jingle bells
  8, 8, 4,  // Jingle bells
  8, 8, 8, 8, 2, // Jingle all the way
  8, 8, 8, 8,    // Oh what fun it is to ride
  8, 8, 8, 8, 4, // In a one-horse open sleigh
  8, 8, 8, 8, 2, // Hey!
  2

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
   for (int thisNote = 0; thisNote <sizeof(melody1) / sizeof(melody1[0]); thisNote++) {
    int noteDuration = 1000 / noteDurations[thisNote];
    tone(9, melody1[thisNote], noteDuration);
    delay(noteDuration * 1.30); // Slight pause between notes

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

  


