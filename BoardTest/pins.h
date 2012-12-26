#include <Arduino.h>

#if defined (BOARD1) || defined(BOARD5) || defined(BOARD7) || defined(BOARD9) 
#define BOARD6
#endif

#ifdef BOARD0
#define ON LOW
#define OFF HIGH
#else
#define ON HIGH
#define OFF LOW
#endif

#if defined(BOARD0) || defined(BOARD6) || defined(BOARDBK)
const bool hasTwoButtons = true;
const int buttonPin1 = 12;
const int buttonPin2 = 13;
#elif defined(BOARD3)
const bool hasTwoButtons = false;
const int buttonPin1= 3;
const int buttonPin2 = buttonPin1;
#elif defined(BOARD4) || defined(BOARD8)
const bool hasTwoButtons = false;
const int buttonPin1= 12;
const int buttonPin2 = buttonPin1;
#endif

#if defined(BOARD0) || defined(BOARD6) || defined (BOARD8)
int pins[] = {
  8,9,10,11,A0,A1,2,3,4,5,6,7}; 
#elif defined(BOARDBK)
int pins[] = {
  8,9,10,11,A1,A0,4,5,2,3,6,7};
#elif defined(BOARD4)
int pins[] = {
  A0,A1,2,3,8,9,10,11,4,5,6,7};
#elif defined(BOARD3)
int pins[] = {
  8,9,12,A1,4,6,11,13,5,7,10,A0};
#endif

#ifdef BOARD2

const bool hasTwoButtons = false;
const int buttonPin1= 12;
const int buttonPin2 = buttonPin1;
int pins[] = {
  8,9,10,11,0,1,2,3,4,5,6,7};

#endif






