/*
Test animations for the 12 LED-Shields
Author: Dr. Blinken
*/

// available boards BOARD0-BOARD9, BOARDBK
#define BOARDBK
#include "pins.h"

int numberleds = 12;
int buttonState1 = 0;    // variable for reading the pushbutton status
int buttonState2 = 0;
int programNumber = 0;  // variable to iterate through the programs
int programCount = 5;

void setup() {
    pinMode(buttonPin1,INPUT);
    pinMode(buttonPin2,INPUT);
    for (int i=0;i<numberleds;i++)
      pinMode(pins[i], OUTPUT);
}

void loop() {

  checkButton();
  switch(programNumber) {
    case 0:
      runner();
      blink();
      chase();
      rows();
      break;
    case 1:
      blink();
      break;
    case 2:
      chase();
      break;
    case 3:
      runner();
      break;
    case 4:
      rows();
      break;
  }

}
void checkButton(){
  buttonState1 = digitalRead(buttonPin1);
  buttonState2 = digitalRead(buttonPin2); // this is garbage if there is no second button
  if ((buttonState1 == ON) || (hasTwoButtons && (buttonState2 == ON))){
    programNumber = (programNumber+1) % programCount;
    buttonAck();
  }
}
void buttonAck(){

  digitalWrite(pins[0],ON);
  digitalWrite(pins[numberleds-1],ON);
  delay(200);

  digitalWrite(pins[0],OFF);
  digitalWrite(pins[numberleds-1],OFF);
}
void allOff(){
  for (int i=0;i<numberleds;i++)
    digitalWrite(pins[i],OFF);
}
void chase(){

  for (int i=0;i<numberleds;i++){
    digitalWrite(pins[i],ON);
    delay(100);
  }
   for (int i=0;i<numberleds;i++){
    digitalWrite(pins[i],OFF);
    delay(100);
  }
}
void blink(){
  for (int i=0;i<2;i++){
  for (int i=0;i<numberleds;i++)
    digitalWrite(pins[i],ON);
  delay(500);
  for (int i=0;i<numberleds;i++)
    digitalWrite(pins[i],OFF);
    delay(500);
  }
}
int ledbefore(int n){
  if (n == 0)
    return numberleds - 1;
  return n-1;
}
void runner(){
  allOff();
  for (int i=0;i<numberleds;i++){
    digitalWrite(pins[i],ON);
    digitalWrite(pins[ledbefore(i)],OFF);
    delay(100);
  }

}

void rows(){
  allOff();
  for (int i=0;i<3;i++){
    for (int j=0;j<4;j++){
       digitalWrite(pins[i*4+j],ON);
    }
    delay(300);
    for (int j=0;j<4;j++){
       digitalWrite(pins[i*4+j],OFF);
    }
  }
 }



