/*************************************************


==================================================
                      1970      
==================================================


FLOPPY LIBRARY: FLOPPY.H
KENO WESTHOFF
HOCHSCHULE FÜR KÜNSTE BREMEN
2016


*************************************************/



#ifndef Floppy_H
#define Floppy_H

#include <WProgram.h>

class Floppy {
  public:

    Floppy();
    ~Floppy();
    void main(int abc, int sec, int min, int h, int d, int m, int y, int modOne, int modTwo, int modThree, int vOne, int vTwo, int vThree, int statOne, int statTwo, int statThree, int statFour);
    int generateMIDI();
    float generateTime();
    float generateDelay();
    bool getX();
    int chaosMode();
    void sendNull();
    void generateB();
    void doTimeshift();
    void findMode();
    
    int timestamp;
    int seconds;
    int minutes;
    int hours;
    int days;
    int months;
    int years;
    
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
    
    
    int melodyCount = 1;
    
    int message = 25;
    float playTime;
    float delayTime;

    // INTERNAL COUNTER FOR THE BEAT
    int count;

    // PERIODS FOR PLAYING CERTAIN TONES
    int microPeriods[108] = {
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      30578, 28861, 27242, 25713, 24270, 22909, 21622, 20409, 19263, 18182, 17161, 16198, //C1 - B1
      15289, 14436, 13621, 12856, 12135, 11454, 10811, 10205, 9632, 9091, 8581, 8099, //C2 - B2
      7645, 7218, 6811, 6428, 6068, 5727, 5406, 5103, 4816, 4546, 4291, 4050, //C3 - B3
      3823, 3609, 3406, 3214, 3034, 2864, 2703, 2552, 2408, 2273, 2146, 2025, //C4 - B4
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
    };

    int arduinoResoultion = 40;
    int note = 10000;
    int magicNumber = (arduinoResoultion * 2);
    int period;
    float a = -400;
    float b;
    float chroma = 25;

    // COMPOSITION BOOLEANS
    bool device_reset;
    bool triggerChaosMode;
    bool triggerOneNote;
    bool triggerCadence;
    bool triggerSine;
    bool triggerTan;
    bool triggerEFu;
    bool triggerLog;
    bool triggerSqrt;
    bool triggerModulation;
    bool triggerCutTime;
    bool triggerJazzy;
    bool triggerChromatic;
    bool triggerWeird;
    bool triggerInter;
    bool triggerMelody;
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
    
    // VARIABLEN, DIE DURCH DAS INTERFACE GESTEUERT WERDEN
    /* float speed = ; // Abspielgeschwindigkeit
    float chaosFactor = ; // Chaosanteil der Komposition
    float b = ; // b (siehe bTriggered)
    float jump = ; // Sprünhr im Takt
    */
};

#endif