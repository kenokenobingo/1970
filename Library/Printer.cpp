/*************************************************


==================================================
                      1970
==================================================


PRINTER LIBRARY: PRINTER.CPP
KENO WESTHOFF
HOCHSCHULE FÜR KÜNSTE BREMEN
2016


*************************************************/



#include "Printer.h"

//EXTERNAL LIBRARIES
#include <util/delay.h>

//DEFINE SERIAL PORT
#define PRINTER_SERIAL Serial3


/*************************************************
<< CONSTRUCTOR >>
*************************************************/

Printer::Printer(){
    PRINTER_SERIAL.begin(9600);
    pinMode(13, OUTPUT);
}


/*************************************************
<< DESTRUCTOR >>
*************************************************/

Printer::~Printer(){/*nothing to destruct*/}

void Printer::main(int abc, int sec, int min, int h, int d, int m, int y, int modOne, int modTwo, int modThree, int vOne, int vTwo, int vThree, int statOne, int statTwo, int statThree, int statFour) {

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

    findMode();

  while (device_reset == 0) {

    sendNull();

    delay(50);

    device_reset = 1;

    _delay_ms(500);

  }

  note = generateMIDI();
  message = (byte) note;
  PRINTER_SERIAL.write(note);

  message = message + map(valueThree, 0, 900, -60, 60);

  digitalWrite(13, HIGH);

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
    if (chroma > 130) {
        chroma = 0;
    }

  //doTimeshift();

  //delay(playTime);

  sendNull();
  //delay(delayTime);
}


/*************************************************
GENERATEMIDI()
GENERATING PITCH
INPUT: NONE
OUTPUT: RETURNS MIDI VALUE, INTEGER
*************************************************/

int Printer::generateMIDI()
{
  if (triggerPanicMode)
  {
    Serial.println("DO PRINTER: PANIC MODE");
    return 0;
  }

  // TRIGGERING ONE NOTE
  if (triggerOneNote)
  {
    Serial.println(" DO PRINTER: ONE NOTE");
    return 44;
  }

  // TRIGGERING CHAOS MODE
  else if (triggerChaosMode) {
    Serial.println("DO PRINTER: CHAOS MODE");
    return chaosMode();
  }

  // TRIGGERING CHORMATIC MODE
  else if (triggerChromatic) {
    Serial.println("DO PRINTER: CHROMATIC");
      return chroma;
  }

   // TRIGGERING SINE MODE
   else if (triggerSine)
   {
     Serial.println("DO PRINTER: SINE");
     //return sin(seconds/minutes) * 256;
     if(!triggerModulation) {
      return abs(128 * sin(6 * seconds));
     } else {
       return abs((128 * sin(6 * seconds)) * (100 * sin(seconds/6)));
      }
    }

    // TRIGGERING TANGENT MODE
    else if (triggerTan)
    {
      Serial.println("DO PRINTER: TANGENT");
      return abs(128 * tan(6 * seconds));
    }

    // TRIGGERING LOGARITHMIC MODE
    else if (triggerLog)
    {
      Serial.println("DO PRINTER: LOGARITHMIC");
      Serial.println((log(sin(seconds)) + exp(1)) * 60);
      return (log(sin(seconds)) + exp(1)) * 60;
    }

    // TRIGGERING SQUARE-ROOT
    else if (triggerSqrt) {
        Serial.println("DO PRINTER: SQAURE-ROOT");
        return sqrt(seconds) * 40;
    }

   // TRIGGERING EXPONENTIAL
   else if (triggerEFu)
   {
      Serial.println("DO PRINTER: EXPONENTIAL");
      return exp(seconds%5);
   }

   // TRIGGERING THE POWER [SIC!]
   else if (triggerPow)
   {
      Serial.println("DO PRINTER: POWER");
      int f = 2;
      return pow(abs(seconds - minutes), 2);
   }

  // TRIGGERING INTER
  else if (triggerInter)
  {
      Serial.println("DO PRINTER: INTER");
      int step;
      int f = 2;
      step = (0.5 * (minutes + seconds) / 10);
      return f * days + step;
  }

  // TRIGGERING WEIRD
  else if (triggerWeird)
  {
      Serial.println("DO PRINTER: WEIRD");
      if (seconds == 60 || seconds == 30 || seconds == 0 || seconds == 15 || seconds == 45) {
        return 42;
      } else {
        int root;
        root = (int) sqrt(years + seconds + minutes + hours);
        return root;
      }
  }
  // NO BLUE NOTE
  else if (triggerCadence && !blueNote) {
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

  // BLUE NOTE
  else if (triggerCadence && blueNote) {
    if (improvisation) {
      int i;

      int Jazzy[] = {44, 47, 48, 49, 50, 51, 54, 55, 56};

        i = (timestamp >> 28) + random (0,2);
        i = i - count;

      if (count == 0) {
        generateB();
        return Jazzy[i] - 12 + b;
      } else if (count == 1) {
        return Jazzy[i] - 12 + b;
      } else if (count == 2) {
        return Jazzy[i] - 12 + b;
      } else if (count == 3) {
        return Jazzy[i] - 12 + b;
      }
    } else if (count == 0) {
      generateB();
      return 44 - 12 + b;
    } else if (count == 1) {
      return 47 - 12 + b;
    } else if (count == 2) {
      return 58 - 12 + b;
    } else if (count == 3) {
      return 60 - 12 + b;
    }
  }
   return 44;
}

/*************************************************
CHAOSMODE()
GENERATING PITCH WITH CHAOS
INPUT: NONE
OUTPUT: RETURNS MIDI VALUE, INTEGER
*************************************************/

int Printer::chaosMode() {
  return random(0, 144);
}

// SILENCE THE DRIVE
void Printer::sendNull() {
    int nix = 0;
    PRINTER_SERIAL.write(nix);
}

// STEPS BETWEEN CADENCES
void Printer::generateB() {
  float Steps[] = { 0, 4, 5, 7, -7, -5, -4, };
  //int i = timestamp % 5;
  int r = map(valueOne, 0, 1023, -1, 2);
  int i = (months / 2) + r;

  if (b > 12 || b < -12) {
    bTriggered = false;
    count++;
  }
}


/*************************************************
CHAOSMODE()
READING INPUTS AND CHOOSING MODE
INPUT: NONE
OUTPUT: NONE
*************************************************/

void Printer::findMode() {
    // LEVER SWITCH #1
    if(modeOne == 1) {
      triggerCadence = true;
      triggerChaosMode = false;
      Serial.println("PRINTER: CADENCE");
  } else if (modeOne == 2) {
      triggerChaosMode = false;
      triggerCadence = false;
      Serial.println("PRINTER: ---");
  }

  // LEVER SWITCH #2
  if (modeTwo == 1) {
      backwards = true;
      Serial.println("PRINTER: BACKWARDS");
  } else if (modeTwo == 2) {
      backwards = false;
      Serial.println("PRINTER: ---");
  }

  // LEVER SWITCH #3
  if (modeThree == 1) {
      triggerJazzy = true;
      blueNote = true;
      Serial.println("PRINTER: JAZZY");
  } else if (modeThree == 2) {
      triggerJazzy = false;
      blueNote = false;
      Serial.println("PRINTER: ---");
  }

// PUSH-BUTTON #1
    if (statusOne == 1) {
        improvisation = true;
        triggerOneNote = false;
        triggerChromatic = false;
        minor = false;
        Serial.println("PRINTER: IMPROVISATION");
    }
    else if (statusOne == 0) {
        improvisation = false;
        triggerOneNote = false;
        triggerChromatic = false;
        minor = false;
        Serial.println("PRINTER: ---");
    }

// PUSH-BUTTON #2
  if (statusTwo == 1) {
        triggerOneNote = true;
        improvisation = false;
        triggerChromatic = false;
        minor = false;
        Serial.println("PRINTER: ONE NOTE");
  }
  else if (statusTwo == 0) {
        triggerOneNote = false;
        improvisation = false;
        triggerChromatic = false;
        minor = false;
        Serial.println("PRINTER: ---");
  }

// PUSH-BUTTON #3
  if (statusThree == 1) {
      triggerChromatic = true;
      triggerOneNote = false;
      improvisation = false;
      minor = false;
      Serial.println("PRINTER: CHROMATIC");
  }
  else if (statusThree == 0) {
      triggerChromatic = false;
      triggerOneNote = false;
      improvisation = false;
      minor = false;
      Serial.println("PRINTER: ---");
  }

// PUSH-BUTTON #4
  if (statusFour == 1) {
      minor = true;
      triggerOneNote = false;
      triggerChromatic = false;
      improvisation = false;
      Serial.println("PRINTER: MINOR");
  }
  else if (statusFour == 0) {
      minor = false;
      triggerOneNote = false;
      triggerChromatic = false;
      improvisation = false;
      Serial.println("PRINTER: ---");
  }
}
