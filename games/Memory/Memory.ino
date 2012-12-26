
/*
Am Anfang jeder Spielrunde blinkt ein Pattern auf, das es zu finden gilt. 
Danach wird alle paar Sekunden ein Pattern angezeigt. Ist es das gesuchte, 
muss der Spieler auf seinen Knopf drücken.

Bei richtiger Antwort gibt es einen Punkt, sonst kriegt der Gegner einen. 
(Der Pfeil, der nach Knopfdruck erscheint, zeigt an, von welchem Spieler 
das Drücken gewertet wurde) 

Nach 5 Runden ist das Spiel vorbei und der Gewinner wird ermittelt. 
*/
#define BOARDBK
#include "pins.h"


int numberleds = 12;
//button stuff
int buttonState1 = 0;    // variable for reading the pushbutton status
int lastButtonState1 = 0;
int buttonState2 = 0;
int lastButtonState2 = 0;
//player stuff
int score1;
int score2;
int clicked = -1;

//game logic stuff
int curMode = 1;
// 1 - startScreen
// 2 - searching
// 3 - clicked
// 4 - end screen
// 5 - show new pattern
int rounds = 5;
int curRound = 1;
int curPattern = -1;
int curDisplayed = -1;
#define patternCount 5
int allPattern[patternCount][12];
//time stuff
int time = 0;
long lastMillis;
int actionAt = 2000;

void setup() { 
  pinMode(buttonPin1,INPUT);
  for (int i=0;i<numberleds;i++)
    pinMode(pins[i], OUTPUT); 

  randomSeed(analogRead(2));
  lastMillis = millis();
  setupPattern();
}

void setupPattern() {
  int count = 0;
  while (count < patternCount) {
    int* s = createPattern();
    
    //check if scheme exist
    for(int i = 0; i < count; i++) {
      if(patternEqual(s,&allPattern[i][0])) {
        continue;
      }
    }
    copyPattern(s,&allPattern[count++][0]);
  }
}

void copyPattern(int* from, int*to) {
 for(int i = 0; i < 12; i++) {
  to[i] = from[i];
 } 
}

int* createPattern() {
  int s[12];
  for(int i = 0; i < 12; i++) {
    if(random(100) <= 50) {
      s[i] = ON;
    } 
    else {
      s[i] = OFF;
    }
  }

  return &s[0];
}

boolean patternEqual(int* s1, int* s2) {
  for(int i = 0; i < 12; i++) {
    if(s1[i] != s2[i]) return false;
  }
  return true;
}

void loop() {

  checkForAction();  
  checkButton();  

  if(buttonState1 == ON && lastButtonState1 == OFF) {
    clicked = 1;
    time = 10000;
    curMode = 3;
  }

  if(buttonState2 == ON && lastButtonState2 == OFF) {
    clicked = 2;
    time = 10000;
    curMode = 3;    
  }
}


void checkForAction() {
  long curMillis = millis();

  time += curMillis - lastMillis;
  lastMillis = curMillis;
  if(time >= actionAt) {
    if(curMode == 1) {
      for(int i = 0; i < patternCount; i++) {
        displayPattern(allPattern[i]);
        delay(750);
      }
      curMode = 5;
    }
    if(curMode == 2) {
      clearScreen();
      delay(500);
      int p = rand() % patternCount;
      curDisplayed = p;
      displayPattern(allPattern[p]);
    }
    if(curMode == 3) {
      if(clicked == 1) arrowRightScreen();
      if(clicked == 2) arrowLeftScreen();
      delay(1000);
      if(curDisplayed == curPattern) {
        if(clicked == 1) score1++;
        if(clicked == 2) score2++;
        correctScreen();
      } 
      else {
        if(clicked == 1) score2++;
        if(clicked == 2) score1++;      
        wrongScreen();
      }

      delay(2000);

      if(rounds == curRound++) {
        curMode = 4;
      } 
      else {
        curMode = 5;
      }
    }
    if(curMode == 4) {
      if(score1 < score2) {
        arrowLeftScreen();
      } 
      else {
        arrowRightScreen();
      }
    }
    if(curMode == 5) {
      int p = rand() % patternCount;
      curPattern = p;
      curDisplayed = -1;
      clearScreen();
      delay(1000);
      displayPattern(allPattern[p]);
      delay(500);
      clearScreen();
      delay(500);
      displayPattern(allPattern[p]);
      delay(500);
      clearScreen();
      delay(500);
      displayPattern(allPattern[p]);
      delay(2000);
      clearScreen();
      delay(1000);
      curMode = 2;
    }
    time = 0;
  }
}

void displayPattern(int p[]) {
  clearScreen();
  for(int i = 0; i < 12; i++) {
    digitalWrite(pins[i],p[i]);
  }
}

void checkButton(){
  lastButtonState1 = buttonState1;
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

void correctScreen() {
  digitalWrite(pins[0],ON);
  digitalWrite(pins[1],OFF);
  digitalWrite(pins[2],OFF);
  digitalWrite(pins[3],OFF);
  digitalWrite(pins[4],OFF);
  digitalWrite(pins[5],ON);
  digitalWrite(pins[6],OFF);
  digitalWrite(pins[7],ON);
  digitalWrite(pins[8],OFF);
  digitalWrite(pins[9],OFF);
  digitalWrite(pins[10],ON);
  digitalWrite(pins[11],OFF);
}

void wrongScreen() {
  digitalWrite(pins[0],ON);
  digitalWrite(pins[1],OFF);
  digitalWrite(pins[2],ON);
  digitalWrite(pins[3],OFF);
  digitalWrite(pins[4],OFF);
  digitalWrite(pins[5],ON);
  digitalWrite(pins[6],OFF);
  digitalWrite(pins[7],OFF);
  digitalWrite(pins[8],ON);
  digitalWrite(pins[9],OFF);
  digitalWrite(pins[10],ON);
  digitalWrite(pins[11],OFF);
}

void arrowLeftScreen() {
  digitalWrite(pins[0],OFF);
  digitalWrite(pins[1],OFF);
  digitalWrite(pins[2],ON);
  digitalWrite(pins[3],OFF);
  digitalWrite(pins[4],ON);
  digitalWrite(pins[5],ON);
  digitalWrite(pins[6],ON);
  digitalWrite(pins[7],ON);
  digitalWrite(pins[8],OFF);
  digitalWrite(pins[9],OFF);
  digitalWrite(pins[10],ON);
  digitalWrite(pins[11],OFF);
}

void arrowRightScreen() {
  digitalWrite(pins[0],OFF);
  digitalWrite(pins[1],ON);
  digitalWrite(pins[2],OFF);
  digitalWrite(pins[3],OFF);
  digitalWrite(pins[4],ON);
  digitalWrite(pins[5],ON);
  digitalWrite(pins[6],ON);
  digitalWrite(pins[7],ON);
  digitalWrite(pins[8],OFF);
  digitalWrite(pins[9],ON);
  digitalWrite(pins[10],OFF);
  digitalWrite(pins[11],OFF);
}

