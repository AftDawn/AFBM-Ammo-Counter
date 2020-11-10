#include <Arduino.h>
#include "AFBM4026.h"

AFBM_4026::AFBM_4026(int tensPin, int onesPin, int resetPin){
    pinMode(tensPin, OUTPUT);
    pinMode(onesPin, OUTPUT);
    pinMode(resetPin, OUTPUT);
}

void AFBM_4026::sendNum(int number){
  int tens = 0;
  int ones = 0;
  tens = number / 10;
  ones = number % 10;


  delay(1);
  digitalWrite(resetPin, HIGH);
  delay(1);
  digitalWrite(resetPin, LOW);

  int pulseTens = tens;
  while(pulseTens > 0){
    digitalWrite(tensPin, HIGH);
    delay(1);
    digitalWrite(tensPin, LOW);
    delay(1);
    pulseTens--;
  }
  
  int pulseOnes = ones;
  while(pulseOnes > 0){
    digitalWrite(onesPin, HIGH);
    delay(1);
    digitalWrite(onesPin, LOW);
    delay(1);
    pulseOnes--;
  }
}