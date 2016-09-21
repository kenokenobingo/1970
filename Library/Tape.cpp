/*************************************************


==================================================
                      1970
==================================================


TAPE LIBRARY: TAPE.CPP
KENO WESTHOFF
HOCHSCHULE FÜR KÜNSTE BREMEN
2016


*************************************************/



#include "Tape.h"

// EXTERNAL LIBRARIES
#include <util/delay.h>

// DEFINING SERIAL PORT
#define TAPE_SERIAL Serial2

const byte pin = 2;
const byte nix = 0;
const byte reset = 100;

// <<CONSTRUCTOR>>
Tape::Tape(){
    TAPE_SERIAL.begin(9600);
    pinMode(13, OUTPUT);
}

// <<DESTRUCTOR>>
Tape::~Tape() { /* NOTHING TO DESTRUCT */ }

void Tape::main(int abc, int sec, int min, int h, int d, int m, int y, int modOne, int modTwo, int modThree, int vOne, int vTwo, int vThree, int statOne, int statTwo, int statThree, int statFour) {

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

  while (device_reset == 0)
  {
    TAPE_SERIAL.write(nix);
    digitalWrite(13, LOW);

    delay(250);

    device_reset = 1;

    _delay_ms(500);
  }

  // GENERATE MIDI MESSAGE
  message = generateMIDI();

  // PRINT MESSAGE IN THE CONSOLE
  Serial.println(message);

  message = message + map(valueThree, 0, 900, -60, 60);
  message = map(message, 0, 128, 0, 255);
  note = microPeriods[message];
  period = note / magicNumber;

  // SEND THE NESSAGE TO THE TAPE CONTROL
  message = abs(message);
  TAPE_SERIAL.write(message);

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
    if (chroma > 75) {
        chroma = 25;
    }

  doTimeshift();

  const int minPlayTime = -20;
  const int maxPlayTime = 20;
  const int minDelayTime = -20;
  const int maxDelayTime = 20;

  // RE-CALCULATE TIME
  playTime = playTime + map(valueOne, 0, 1023, minPlayTime, maxPlayTime);
  delayTime = delayTime + map(valueTwo, 0, 1023, -minPlayTime, maxPlayTime);

  // SUSATAIN NOTE
  delay(playTime);

  // SILENCE THE DRIVE
  //sendNull();

  // SUSTAIN SILENCE
  delay(delayTime);

/*
  TAPE_SERIAL.write(pin);
  TAPE_SERIAL.write(nix); */
  //TAPE_SERIAL.write(nix);

  // INTERNAL LED OFF
  digitalWrite(13, LOW);
}


/*************************************************
GENERATEMIDI()
GENERATING PITCH
INPUT: NONE
OUTPUT: RETURNS MIDI VALUE
*************************************************/
int Tape::generateMIDI() {

    if (triggerPanicMode)
    {
      Serial.println("TAPE: PANIC MODE");
      return panicMode();
    }

    // TRIGGERING CHAOS MODE
    if (triggerChaosMode)
    {
      Serial.println("TAPE: CHAOS");
      return chaosMode();
    }

    // TRIGGERING HICK HACK
    else if (triggerHickHack)
    {
      Serial.println("TAPE: HICK HACK");
      if (seconds == 1 || seconds == 2 || seconds == 3 || seconds == 4 || seconds == 5 || seconds == 30 || seconds == 31 || seconds == 32 || seconds == 33 || seconds == 34 || seconds == 35) {
          return seconds * 2;
      } else {
          return seconds;
      }
      return 0;
    }

    // TRIGGERING JUMPING VALUES
    else if (triggerJump)
    {
      Serial.println("TAPE: JUMP");

      int x = months * random(0, months);
      int f = 2;

      return (days + x) * f;
    }

    // TRIGGERING SINE MODE
    else if (triggerSine)
    {
      Serial.println("TAPE: SINE");
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
      Serial.println("TAPE: TANGENT");
      return abs(128 * tan(6 * seconds));
    }

    // TRIGGERING EXPONENTIAL MODE
    else if (triggerLog)
    {
      Serial.println("TAPE: LOGARITHMIC");
      Serial.println((log(sin(seconds)) + exp(1)) * 60);
      return (log(sin(seconds)) + exp(1)) * 60;
    }

    // TRIGGERING SQUARE-ROOT
    else if (triggerSqrt) {
        Serial.println("TAPE: SQAURE-ROOT");
        return sqrt(seconds) * 40;
    }

   // TRIGGERING EXPONENTIAL
   else if (triggerEFu)
   {
      Serial.println("TAPE: EXPONENTIAL");
      return exp(seconds%5);
   }

   // TRIGGERING THE POWER [SIC!]
   else if (triggerPow)
   {
      Serial.println("TAPE: POWER");
      int f = 2;
      return pow(abs(seconds - minutes), 2);
   }

   // TRIGGERING BREAK MODE
   else if (triggerBreak)
   {
      Serial.println("TAPE: BREAK");
      for (int i=0; i<=seconds+months; i++) {
      return seconds * 2;
      }
      return 0;
   }

    // TRIGGERING STUTTERING MODE
   else if (triggerStutter)
   {
      Serial.println("TAPE: STUTTER");

      counting++;
      Serial.println(counting);

      if (counting >= 2) {
          counting = 0;
      }

      if (counting < 1) {
      return months * factor;
      } else {
      return factor; }

      return 0;
   }

    // TRIGGERING NOTHING
   else if (triggerNull)
   {
      Serial.println("TAPE: NULL");
      return 0;
   }

    // TRIGGERING CHROMATIC MODE
   else if (triggerChromatic)
   {
      Serial.println("TAPE: CHROMA");
      return chroma;
   }

    // TRIGGERING INTER MODE
   else if (triggerInter)
   {
      Serial.println("TAPE: INTER");
      int step;
      step = seconds / 5 - minutes % 4;
      return months * days + step;
   }

    // TRIGGERING WEIRD MODE
   else if (triggerWeird)
   {
      Serial.println("TAPE: WEIRD");
      if (seconds < 60 && seconds > 30) {
          return 42;
      } else {
      return sqrt(years);
      }
   }

    // TRIGGERING ONE NOTE MODE
   else if (triggerOneNote)
   {
    Serial.println("TAPE: ONE NOTE");
    //return (int) timestamp >> 24;
    return 44;
   }

   // TRIGGERING CADENCE MODE
   else if (triggerCadence && !blueNote)
   {
     Serial.println("TAPE: CADENCE");
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

   // TRIGGERING JAZZY MODE
   else if (triggerCadence && blueNote)
   {
      Serial.println("TAPE: JAZZY");

      counting++;
      Serial.println(counting);

      if (counting > 2) {
          counting = 0;
      }
   }

if (counting == 1 || counting == 2) {
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
  } else if (triggerMelody) {
      Serial.println("TAPE: MELODY");
      Serial.println("MC" + melodyCount);
      if (melodyCount == 1 || melodyCount == 2 || melodyCount == 7) {
          melodyCount++;
          return 46;
      } else if (melodyCount == 3 || melodyCount == 6) {
          melodyCount++;
          return 47;
      } else if (melodyCount == 4 || melodyCount == 5) {
          melodyCount++;
          return 49;
      } else {
          melodyCount = 1;
          return 0;
      }
  } else {
      return 10;
  }

      return 190;
}

// CHAOS MODE
// OUTPUT: RETURNS MIDI VALUE FOR PITCH
int Tape::panicMode() {
  int midiMin = 0;
  int midiMax = 127;
  return random(midiMin, midiMax);
}

// CHAOS MODE
// OUTPUT: RETURNS MIDI VALUE FOR PITCH
int Tape::chaosMode() {
  return random(seconds, minutes);
}

// SILENCE THE DRIVE
void Tape::sendNull() {
  TAPE_SERIAL.write(nix);
}

/************************************************
GENERATEB()
CALCULATING STEPS BETWEEN CADENCES
INPUT: NONE
OUTPUT: NONE
*************************************************/
void Tape::generateB() {
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

void Tape::doTimeshift () {
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

// READ INPUTS
// CHOOSING MODE
void Tape::findMode() {

    if(modeOne = 1 && modeTwo == 1 && modeThree == 1 && statusOne == 1 && statusTwo == 1 && statusThree == 1 && statusFour == 1)
    {
        Serial.println("TAPE ACTIVIATED.");
        triggerPanicMode = true;
    }

    // LEVER SWITCH #1
    if(modeOne == 1) {
      triggerHickHack = true;
      Serial.println("HICKHACK ACTIVATED.");
  } else if (modeOne == 2) {
      triggerHickHack = false;
      Serial.println("HICKHACK DEACTIVATED.");
  }

  // LEVER SWITCH #2
  if (modeTwo == 1) {
      triggerSine = true;
      Serial.println("SINE ACTIVATED.");
  } else if (modeTwo == 2) {
      triggerSine = false;
      Serial.println("SINE DEACTIVATED.");
  }

  // LEVER SWITCH #3
  if (modeThree == 1) {
      triggerWeird = true;
      Serial.println("WERID ACTIVATED.");
  } else if (modeThree == 2) {
      triggerWeird = false;
      Serial.println("WEIRD DEACTIVATED.");
  }

  // PUSH-BUTTON #1
    if (statusOne == 1)
    {
        improvisation = true;
        Serial.println("IMPROVISATION ACTIVATED.");
    }
    else if (statusOne == 0)
    {
        improvisation = false;
        Serial.println("IMPROVISATION DEACTIVATED.");
    }

// PUSH-BUTTON #2
  if (statusTwo == 1)
  {
        triggerOneNote = true;
        Serial.println("ONE NOTE ACTIVATED.");
  }
  else if (statusTwo == 0)
  {
        triggerOneNote = false;
        Serial.println("ONE NOTE DEACTIVATED.");
  }

// PUSH-BUTTON #3
  if (statusThree == 1)
  {
      triggerChromatic = true;
      triggerHickHack = false;
      triggerSine = false;
      Serial.println("CHROMATIC ACTIVATED.");
  }
  else if (statusThree == 0)
  {
      triggerChromatic = false;
      Serial.println("CHROMATIC DEACTIVATED.");
  }

// PUSH-BUTTON #4
  if (statusFour == 1)
  {
      minor = true;
      Serial.println("MINOR ACTIVATED.");
  }
  else if (statusFour == 1)
  {
      minor = false;
      Serial.println("MINOR DEACTIVATED.");
  }
}

/*************************************************
GENERATETIME()
GENERATING DURATION OF A NOTE
INPUT: NONE
OUTPUT: RETURNS DURATION OF A NOTE, FLOAT
*************************************************/

float Tape::generateTime() {
  float x;

  if (triggerWeird) {
      return seconds * 0.5;
  }

  if (triggerInter) {
      int interVal = days/months;
      return interVal;
  }

  if (triggerChromatic) {
      return 5;
  }

  if (triggerLog) {
      return log(seconds);
  }

  if (yearIsTime) {
      return years;
  }

  if (triggerSine) {
      const int yearDays = 365;
      return abs(yearDays * sin(years));
  }

  // TRIGGERING THE POWER [SIC!]
  if (triggerPow) {
      int f = 2;
      return pow(abs(seconds - minutes), f);
  }

  if (triggerTan) {
      return abs(365 * tan(years));
  }

  if (triggerLog) {
      return 365 * log(years);
  }

  if (triggerSqrt) {
      return sqrt(years) + 365;
  }

  if (triggerEFu) {
      return exp(years % 2) + years;
  }

  if (triggerCadence) {
      return years / months;
  }

  if (triggerMelody) {
      int f = 50;
      return hours * f;
  }

  if (accelerating) {
    a = a - months;
    if (a <= 50) {
      accelerating = false;
      decelerating = true;
    }
  } else if (decelerating) {
    (a = a + days);
    if (a > 500) {
      accelerating = true;
      decelerating = false;
    }
  } else {
    a = 0;
  }

  // PICKING VALUES
  if (pickTime) {
      bool method = (bool) random(0,2);
      if (method) {
      Serial.println("TAPE: PICKTIME TIMESTAMP");
      float Time[] = {50, 75, 100, 125, 150, 175, 200, 250, 300, 400, 500};
        int i = timestamp >> 28;
        return Time[i];
     } else {
        Serial.println("TAPE: PICKTIME MONTHS");
        return months * seconds;
  }
}

  // TIME WARP
  triggerCutTime = getX();

  if (triggerCutTime) {
    if (triggerJazzy) {
      x = (3 + (1 / 3));
    } else {
      x = 2;
    }
  } else {
    x = 1;
  }

  if (triggerWeird) {
      return 0;
  }

  if (triggerChaosMode) {
   // return (minutes * seconds) + a;
      bool oneOrAnother;

      int a = random(0,2);

      if (a < 1) {
          oneOrAnother = true;
      } else {
          oneOrAnother = false;
      }


      if (oneOrAnother) {
          return (minutes * seconds) + a;
      } else {
          return years;
      }
  } else if (triggerOneNote || (triggerCadence && !triggerJazzy)) {
    return ((timestamp >> 22) * x) + a;
  } else if (triggerCadence && triggerJazzy) {
    //return ((timestamp >> 20) * x) + a;
    return ((seconds) * x) + a;
  } else {
    return ((timestamp >> 21) * x) + a;
  }

    if (triggerCadence) {
      return 50;
    }
}

// GENERATE TIME BETWEEN NOTES
float Tape::generateDelay() {
  float x;

  if (triggerMelody) {
      int f = 10;
      return hours * f;
  }

  if (triggerSine) {
      return 0;
  }

  if (triggerWeird) {
      return 100;
  }

  if (triggerInter) {
      int interValDel = months/years;
      return interValDel;
  }

  if (triggerChromatic) {
      return 5;
  }

  // PICKING VALUES
  if (pickTime) {
    bool longOrShort = true;
    int i;
    float Time[] = {5, 10, 20, 50, 15, 20, 25, 50, 100, 400, 500};

    if (longOrShort) {
      i = timestamp >> 27;
    } else {
      i = timestamp >> 28;
    }

    return Time[i];
    Serial.println(Time[i]);
  }

  if (triggerJazzy) {
    return 10;
  }

  if (accelerating) {
    a = a - 20;
    if (a <= 50) {
      accelerating = false;
      decelerating = true;
    }
  } else if (decelerating) {
    (a = a + 10);
    if (a > 500) {
      accelerating = true;
      decelerating = false;
    }
  } else {
    a = 0;
  }

  triggerCutTime = getX();

  if (triggerCutTime) {
    x = 2;
  } else {
    x = 1;
  }

  if (triggerChaosMode) {
    return (random(10, 100) * x) + a;
  } else if (triggerOneNote || triggerCadence) {
    return ((timestamp >> 25) * x) + a;
  } else {
    return ((timestamp >> 21) * x) + a;
  }
}


/************************************************
GETX()
DETERMINING IF TIME WARP SHOULD BE TRIGGERED (TRIGGERCUTTIME)
INPUT: NONE
OUTPUT: TRIGGER TRUE OR FALSE, BOOLEAN
*************************************************/

bool Tape::getX() {
  if (count == 0) {
        return true;
  } else if (count == 1) {
        return false;
  } else if (count == 2) {
        return true;
  } else if (count == 3) {
        return false;
  } else {
        return false;
  }
return false;
}
