#include <Arduino.h>
#include "Dice.h"

const int numbers[][12] = {
  {0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,1,0,0,0,0,0,0}
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


