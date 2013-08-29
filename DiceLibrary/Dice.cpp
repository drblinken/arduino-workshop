#include <Arduino.h>
#include "Dice.h"
#include "pins.h"

// use the ON/OFF abstraction from pins.h
#define O OFF
#define X ON
const int numbers[][12] = {
  {O,O,O,O,O,O,O,O,O,O,O,O},
  {O,O,O,O,O,X,O,O,O,O,O,O}
  // ...
};



Die::Die(int numberleds,int* pins){
  this->pins = pins;
  this->numberleds = numberleds;
  randomSeed(analogRead(0));
}
void Die::roll(){
   
}
  
void Die::showNumber(int number){
}


