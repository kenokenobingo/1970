/*************************************************


   ==================================================
                      1970
   ==================================================


   FLOPPY LIBRARY: FLOPPY.CPP
   KENO WESTHOFF
   HOCHSCHULE FÜR KÜNSTE BREMEN
   2016


*************************************************/



#include "Floppy.h"


// EXTERNAL LIBRARIES
#include <util/delay.h>


// DEFINING SERIAL PORT
#define FLOPPY_SERIAL Serial1


const byte pin = 2;
const byte nix = 0;
const byte reset = 100;


/*************************************************
   << CONSTRUCTOR >>
*************************************************/

Floppy::Floppy(){
        FLOPPY_SERIAL.begin(9600);
        pinMode(13, OUTPUT);
}


/*************************************************
   << DESTRUCTOR >>
*************************************************/

Floppy::~Floppy(){ /* NOTHING TO DESTRUCT */
}


void Floppy::main(int abc, int sec, int min, int h, int d, int m, int y, int modOne, int modTwo, int modThree, int vOne, int vTwo, int vThree, int statOne, int statTwo, int statThree, int statFour) {

        timestamp = abc;
        seconds = sec;
        minutes = min;
        hours = h;
        days = d;
        months = m;
        years = y;

        modeOne = modOne;
        modeTwo = modTwo;
        modeThree = modThree;

        valueOne = vOne;
        valueTwo = vTwo;
        valueThree = vThree;

        statusOne = statOne;
        statusTwo = statTwo;
        statusThree = statThree;
        statusFour = statFour;

        while (device_reset == 0) {
                FLOPPY_SERIAL.write(reset);

                FLOPPY_SERIAL.write(pin);
                FLOPPY_SERIAL.write(nix);
                FLOPPY_SERIAL.write(nix);
                digitalWrite(13, LOW);

                delay(50);

                device_reset = 1;

                _delay_ms(500);
        }

        // LEVER SWITCH #1
        if(modeOne == 1) {

                goDoThings();

        } else if (modeOne == 2) {
                message = 0;
                playTime = 0;
                delayTime = 0;

                triggerCadence = false;
                triggerOneNote = false;
                triggerCadence = false;
                triggerSine = false;

                FLOPPY_SERIAL.write(nix);
                Serial.println("FLOPPY: SILENCE");
        }

}


/*************************************************
   GENERATEMIDI()
   GENERATING PITCH
   INPUT: NONE
   OUTPUT: RETURNS MIDI VALUE, INTEGER
*************************************************/

int Floppy::generateMIDI() {

        // TRIGGERING CADENCE
        if (triggerCadence) {
                Serial.println("DO FLOPPY: CADENCE");
                if (count == 0) {
                        generateB();
                        return 44 - 12 + b;
                } else if (count == 1) {
                        if (minor) {
                                return 47 - 12 + b;
                        } else {
                                return 48 - 12 + b;
                        }
                } else if (count == 2) {
                        return 51 - 12 + b;
                } else if (count == 3) {
                        return 44 - 12 + b;
                }
        }

        // TRIGGERIN ONE NOTE
        else if (triggerOneNote)
        {
                Serial.println("DO FLOPPY: ONE NOTE");
                //return (int) timestamp >> 24;
                return 44;
        }

        // TRIGGERING CHROMATIC
        else if (triggerChromatic)
        {
                Serial.println("DO FLOPPY: CHROMATIC");
                return chroma;
        }

        // TRIGGERING SINE
        else if (triggerSine)
        {
                Serial.println("DO FLOPPY: SINE");
                if(!triggerModulation) {
                        return abs(40 * sin(6 * seconds) + 30);
                } else {
                        return abs(((40 * sin(6 * seconds)) + 30) * (25 * sin(seconds/6)));
                }
        }

        // FALLBACK
        return 44;
}


/*************************************************
   GENERATETIME()
   GENERATING DURATION OF A NOTE
   INPUT: NONE
   OUTPUT: RETURNS DURATION OF A NOTE, FLOAT
*************************************************/

float Floppy::generateTime() {

        if (triggerCadence) {
                return seconds;
        }

        else if (triggerOneNote) {
                return years;
        }

        else if (triggerChromatic) {
                return seconds;
        }

        else if (triggerSine) {
                return abs(365 * sin(years));
        }

}

// GENERATE TIME BETWEEN NOTES
float Floppy::generateDelay() {

        if (triggerCadence) {
                return 5;
        }

        else if (triggerOneNote) {
                return 10;
        }

        else if (triggerChromatic) {
                return 5;
        }

        else if (triggerSine) {
                return 0;
        }

}


void Floppy::doTimeshift () {
        if (timeshift) {
                int i = timestamp % 7;
                //int i = random(0,2);

                count = count + i;
        }

        if (b == 6 || b == -4) {
                count = count + 1;
                b++;
        }

        if (b == 2) {
                count = 3;
                b = 0;
        }
}


/************************************************
   GENERATEB()
   CALCULATING STEPS BETWEEN CADENCES
   INPUT: NONE
   OUTPUT: NONE
 *************************************************/
void Floppy::generateB() {
        float Steps[] = { -7, -5, -4, 0, 4, 5, 7};
        //int i = timestamp % 5;
        //int r = random(-1, 2);
        int r = map(valueOne, 0, 1023, -1, 2);
        int i = (months / 2) + r;

        if (b > 12 || b < -12) {
                bTriggered = false;
                count++;
        }

        if (!bTriggered) {
                b = timestamp >> 28;
                bTriggered = true;
        } else {
                //PICKING A VALUE
                b = b + Steps[i];
        }
}


/************************************************
   SENDNULL()
   SILENCING THE DRIVE
   INPUT: NONE
   OUTPUT: NONE
 *************************************************/

void Floppy::sendNull() {
        FLOPPY_SERIAL.write(pin);
        FLOPPY_SERIAL.write(nix);
        FLOPPY_SERIAL.write(nix);
}


// READ INPUTS
// CHOOSING MODE
void Floppy::findMode() {

// PUSH-BUTTON #1
        if (statusOne == 1) {
                triggerCadence = true;
                triggerOneNote = false;
                triggerCadence = false;
                triggerSine = false;
                Serial.println("FLOPPY: CADENCE");
        }
        else if (statusOne == 0) {
                triggerCadence = false;
                Serial.println("FLOPPY: ---");
        }

// PUSH-BUTTON #2
        if (statusTwo == 1) {
                triggerOneNote = true;
                triggerCadence = false;
                triggerChromatic = false;
                triggerSine = false;
                Serial.println("FLOPPY: ONE NOTE");
        }
        else if (statusTwo == 0) {
                triggerPanicMode = false;
                Serial.println("FLOPPY: ---");
        }

// PUSH-BUTTON #3
        if (statusThree == 1) {
                triggerChromatic = true;
                triggerOneNote = false;
                triggerCadence = false;
                triggerSine = false;
                Serial.println("FLOPPY: CHROMATIC");
        }
        else if (statusThree == 0) {
                triggerChromatic = false;
                Serial.println("FLOPPY: ---");
        }

// PUSH-BUTTON #4
        if (statusFour == 1) {
                triggerSine = true;
                triggerOneNote = false;
                triggerChromatic = false;
                triggerCadence = false;
                Serial.println("FLOPPY: SINE");
        }
        else if (statusFour == 1) {
                triggerSine = false;
                Serial.println("FLOPPY: ---");
        }
}

void Floppy::goDoThings() {

        findMode();
        message = generateMIDI();
        playTime = generateTime();
        delayTime = generateDelay();
        Serial.println("FLOPPY: GO");

        /* --- */

        // PRINT MESSAGE IN THE CONSOLE
        Serial.println(message);

        message = message + map(valueThree, 0, 1023, -10, 10);
        note = microPeriods[message];
        period = note / magicNumber;
        //int period = (int) (currentPeriod[message.getStatus() - 224] / Math.pow(2.0, (BEND_CENTS/1200.0)*((pitchBend - 8192.0) / 8192.0)));

        // SPLIT THE MESSAGE INTO TWO BYTES
        byte partOne = (byte) ((period >> 8) & 0xFF);
        byte partTwo = (byte) ((period) & 0xFF);

        // SEND THE NESSAGE TO THE FLOPPY DRIVE CONTROL
        FLOPPY_SERIAL.write(pin);
        FLOPPY_SERIAL.write(partOne);
        FLOPPY_SERIAL.write(partTwo);

        // PRINT THE MESSAGE IN THE CONSOLE
        Serial.println(pin);
        Serial.println(partOne);
        Serial.println(partTwo);

        // INTERNAL LED ON
        digitalWrite(13, HIGH);

        // PLAYING NOTES BACKWARDS
        if (backwards) {
                if (count > 0) {
                        count = count - 1;
                } else {
                        count = 3;
                }
        } else {
                if (count < 3) {
                        count++;
                } else {
                        count = 0;
                }
        }

        if (note == 44) {
                timeshift = true;
        }

        chroma++;
        if (chroma > 72) {
                chroma = 25;
        }

        doTimeshift();

        // RE-CALCULATE TIME
        playTime = playTime + map(valueOne, 0, 100, -200, 200);
        delayTime = delayTime + map(valueTwo, 0, 1023, -200, 200);

        // SUSATAIN NOTE
        delay(playTime);

        // SILENCE THE DRIVE
        sendNull();

        // SUSTAIN SILENCE
        delay(delayTime);

        // INTERNAL LED OFF

}
