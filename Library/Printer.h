/*************************************************


==================================================
                      1970      
==================================================


PRINTER LIBRARY: PRINTER.H
KENO WESTHOFF
HOCHSCHULE FÜR KÜNSTE BREMEN
2016


*************************************************/



#ifndef Printer_H
#define Printer_H

#include <WProgram.h>

class Printer {
  public:

    Printer();
    ~Printer();
    void main(int abc, int sec, int min, int h, int d, int m, int y, int modOne, int modTwo, int modThree, int vOne, int vTwo, int vThree, int statOne, int statTwo, int statThree, int statFour);
    void findMode();
    int generateMIDI();
    float generateTime();
    float generateDelay();
    bool getX();
    int chaosMode();
    void generateMessage(int input);
    void sendNull();
    void generateB();
    void doTimeshift();
    
    int modeOne;
    int modeTwo;
    int modeThree;
    
    int valueOne;
    int valueTwo;
    int valueThree;
        
    int statusOne;
    int statusTwo;
    int statusThree;
    int statusFour;
    
    bool turnOne;
    bool turnTwo;
    bool turnThree;
    bool turnFour;
    bool turnFive;
    
    int timestamp;
    int seconds;
    int minutes;
    int hours;
    int days;
    int months;
    int years;
    
    int message = 25;
    float playTime;
    float delayTime;

    int count;

    int note = 10;
    float a = -400;
    float b;
    float chroma = 25;

    // COMPOSITION BOOLEANS
    bool device_reset;
    bool triggerChaosMode;
    bool triggerOneNote;
    bool triggerCadence;
    bool triggerCutTime;
    bool triggerJazzy;
    bool triggerChromatic;
    bool triggerWeird;
    bool triggerInter;
    bool triggerSine;
    bool triggerTan;
    bool triggerEFu;
    bool triggerLog;
    bool triggerSqrt;
    bool triggerModulation;
    bool triggerPow;
    bool pickTime;
    bool accelerating;
    bool decelerating;
    bool backwards;
    bool bTriggered;
    bool timeshift;
    bool blueNote;
    bool improvisation;
    bool minor;
    bool yearIsTime;
    
    /*
    // PIN BYTES
    byte n0;
    byte n1;
    byte n2;
    byte n3;
    byte n4;
    byte n5;
    byte n6;
    byte n7;
    byte strobe;
    byte autofd;
    */
};

#endif