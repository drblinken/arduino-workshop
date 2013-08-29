/*
Scaffold for a Dice Library
Author: Dr. Blinken
*/
#define BOARD2

#include "pins.h"
int numberleds = 12;

#include "Dice.h"

int buttonState = 0;         // variable for reading the pushbutton status

Die die(numberleds,pins);

void setup() {
    pinMode(buttonPin1,INPUT);
    pinMode(buttonPin2,INPUT);
    for (int i=0;i<numberleds;i++)
      pinMode(pins[i], OUTPUT);
}

void loop() {

}




