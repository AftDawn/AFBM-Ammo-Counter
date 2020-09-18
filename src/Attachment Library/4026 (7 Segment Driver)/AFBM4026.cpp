#include <Arduino.h>
#include "AFBM4026.h"

AFBM_4026::AFBM_4026(int enablePin, int tensPin, int onesPin, int resetPin){
    pinMode(enablePin, OUTPUT);
    pinMode(tensPin, OUTPUT);
    pinMode(onesPin, OUTPUT);
    pinMode(resetPin, OUTPUT);
}

void AFBM_4026::sendNum(int numberToDisplay){
  int tens = 0;
  int ones = 0;
  tens = numberToDisplay / 10;
  ones = numberToDisplay % 10;


  delay(1);
  digitalWrite(enablePin, LOW);
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
  digitalWrite(enablePin, HIGH);
}