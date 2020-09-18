#ifndef 4026_h
#define 4026_h

#include <Arduino.h>

class 4026
{
    public:
        4026Setup(int enable, int tens, int ones, int reset)
        void 4026SendNum(int numberToDisplay);
    private:
    uint8_t currentNum;
};

#endif