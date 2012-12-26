/*
Die linken 3 Pixel sind der Bereich, in dem der Spieler sich mit den Knöpfen
bewegen kann und von rechts kommen Objekte reingeflogen, denen er ausweichen 
muss. 
*/

#define BOARDBK
#include "pins.h"

int numberleds = 12;
int buttonState1 = 0;    // variable for reading the pushbutton status
int lastButtonState = 0;
int buttonState2 = 0;
int lastButtonState2 = 0;
int playerPos = 3;
int enemies[3];
int time = 0;
long lastMillis;
int actionAt = 1500;
int possibility = 40;
boolean gameOver = false;


void setup() { 
    pinMode(buttonPin1,INPUT);
    for (int i=0;i<numberleds;i++)
      pinMode(pins[i], OUTPUT); 
   
   enemies[0] = -1;
   enemies[1] = -1;
   enemies[2] = -1;
   lastMillis = millis();
}

void loop() {
  
  if(gameOver) {
    fillScreen();
    return;
  }
  
  long curMillis = millis();
  
  time += curMillis - lastMillis;
  lastMillis = curMillis;
  if(time >= actionAt) {
    checkCollision();
    if(gameOver)
    return;
    moveEnemies();
    checkEnemyCreation();
    time = 0;
    possibility++;
  }
  
  checkButton();

  if(buttonState1 == ON && lastButtonState == OFF) {
    if(playerPos != 11) {
      playerPos += 4;
    }
  }
  
  if(buttonState2 == ON && lastButtonState2 == OFF) {
    if(playerPos != 3) {
      playerPos -= 4;
    }
  }
  
  clearScreen();
  digitalWrite(pins[playerPos],ON);
  if(enemies[0] != -1)
    digitalWrite(pins[enemies[0]],ON);
  if(enemies[1] != -1)
    digitalWrite(pins[enemies[1]],ON);
  if(enemies[2] != -1)
    digitalWrite(pins[enemies[2]],ON);
//  delay(100);
}

void checkEnemyCreation() {
  int val = (rand() % 100);
  if(val < possibility) {
    createEnemy();
  }
}

void moveEnemies() {
 if(enemies[0] != -1) {
   enemies[0] += 1;
   
   if(enemies[0] == playerPos) {
    gameOver = true; 
   }
   if(enemies[0] > 3) {
    enemies[0] = -1; 
   }
 } 
 
  if(enemies[1] != -1) {
   enemies[1] += 1;
   
   if(enemies[1] == playerPos) {
    gameOver = true; 
   }
   if(enemies[1] > 7) {
    enemies[1] = -1; 
   }
 } 
 
  if(enemies[2] != -1) {
   enemies[2] += 1;
   
   if(enemies[2] == playerPos) {
    gameOver = true; 
   }
   if(enemies[2] > 11) {
    enemies[2] = -1; 
   }
 } 
}

void createEnemy() {
     int freeCount = 0;
    if(enemies[0] == -1 && enemies[1] != 4) freeCount++; 
    if(enemies[1] == -1 && !(enemies[0] != 0 && enemies[2] != 8)) freeCount++; 
    if(enemies[2] == -1 && enemies[1] != 4) freeCount++; 
    
    if(freeCount != 0) {

      boolean success = false;
      while(!success) {
      int val = rand() % 3;
      if(enemies[val] == -1) {
        enemies[val] = val*4; 
        success = true;
      }
      }
    }
}

void checkCollision() {
  if(enemies[0] == playerPos) gameOver = true;
  if(enemies[1] == playerPos) gameOver = true;
  if(enemies[2] == playerPos) gameOver = true;
}

void checkButton(){
  lastButtonState = buttonState1;
  lastButtonState2 = buttonState2;
  buttonState1 = digitalRead(buttonPin1);
  buttonState2 = digitalRead(buttonPin2); // this is garbage if there is no second button
}

void clearScreen() {
  digitalWrite(pins[0],OFF);
  digitalWrite(pins[1],OFF);
  digitalWrite(pins[2],OFF);
  digitalWrite(pins[3],OFF);
  digitalWrite(pins[4],OFF);
  digitalWrite(pins[5],OFF);
  digitalWrite(pins[6],OFF);
  digitalWrite(pins[7],OFF);
  digitalWrite(pins[8],OFF);
  digitalWrite(pins[9],OFF);
  digitalWrite(pins[10],OFF);
  digitalWrite(pins[11],OFF);
}

void fillScreen() {
  digitalWrite(pins[0],ON);
  digitalWrite(pins[1],ON);
  digitalWrite(pins[2],ON);
  digitalWrite(pins[3],ON);
  digitalWrite(pins[4],ON);
  digitalWrite(pins[5],ON);
  digitalWrite(pins[6],ON);
  digitalWrite(pins[7],ON);
  digitalWrite(pins[8],ON);
  digitalWrite(pins[9],ON);
  digitalWrite(pins[10],ON);
  digitalWrite(pins[11],ON);
}
