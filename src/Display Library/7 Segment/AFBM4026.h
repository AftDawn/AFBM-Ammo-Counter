#ifndef AFBM4026_h
#define AFBM4026_h

#include <Arduino.h>

class AFBM_4026
{
    public:
        AFBM_4026(int tensPin, int onesPin, int resetPin);
        void sendNum(int numberToDisplay);
    private:
    uint8_t currentNum;
    uint8_t tensPin;
    uint8_t onesPin;
    uint8_t resetPin;
};

#endif