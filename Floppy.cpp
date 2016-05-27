#include "Floppy.h"

// EXTERNAL LIBRARIES
#include <util/delay.h>

#define FLOPPY_SERIAL Serial1

const byte pin = 2;
const byte nix = 0;
const byte reset = 100;

// <<CONSTRUCTOR>>
Floppy::Floppy(){
    FLOPPY_SERIAL.begin(9600);
    pinMode(13, OUTPUT);
}
 
// <<DESTRUCTOR>>
Floppy::~Floppy(){/*nothing to destruct*/}

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

    findMode();
    
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
    
  //message = generateMIDI();

  playTime = generateTime();
  delayTime = generateDelay();

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
  playTime = playTime + map(valueOne, 0, 1023, -100, 100);
  delayTime = delayTime + map(valueTwo, 0, 1023, -100, 100);
     
  // SUSATAIN NOTE
  delay(playTime);

  // SILENCE THE DRIVE    
  sendNull();
    
  // SUSTAIN SILENCE
  delay(delayTime);

/*
  FLOPPY_SERIAL.write(pin);
  FLOPPY_SERIAL.write(nix);
  FLOPPY_SERIAL.write(nix); */
    
  // INTERNAL LED OFF    
  digitalWrite(13, LOW);
}

// GENERATING PITCH
int Floppy::generateMIDI() {
  //return (int) timestamp >> 24;
  if (triggerChaosMode) {
    return chaosMode();
  } else if (triggerChromatic) {
      return chroma;
  } else if (triggerInter) {
    int step;
    step = seconds / 5 - minutes % 4;
    return months * days + step;
  } else if (triggerWeird) {
      if (seconds == 60 || seconds == 30 || seconds == 0 || seconds == 15 || seconds == 45) {
          return 42;
      } else {
      return sqrt(years);
      }
  } else if (triggerOneNote) {
    //return (int) timestamp >> 24;
    return 44;
  } else if (triggerCadence && !blueNote) {
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
  } else if (triggerCadence && blueNote) {
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
      
      return 0;
  }
   return 44; 
}

// GENERATE DURATION OF A NOTE
float Floppy::generateTime() {
  float x;
    
  if (triggerWeird) {
      return seconds;
  } 
    
  if (triggerInter) {
      int interVal = days/months;
      return interVal;
  }
    
  if (triggerChromatic) {
      return 20;
  }
    
  if (yearIsTime) {
      return years;
  }
    
  if (triggerCadence) {
      return years / months;
  }
    
  if (triggerMelody) {
      return 10;
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
      float Time[] = {50, 75, 100, 125, 150, 175, 200, 250, 300, 400, 500};
        int i = timestamp >> 28;
        return Time[i];
     } else {   
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
float Floppy::generateDelay() {
  float x;
    
  if (triggerMelody) {
      return 0;
  }
    
  if (triggerWeird) {
      return 0;
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
    return 50;
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

// DETERMINING IF TIME WARP SHOULD BE TRIGGERED (TRIGGERCUTTIME)
bool Floppy::getX() {
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

// CHAOS MODE
int Floppy::chaosMode() {
  return random(24, 92);
}

// SILENCE THE DRIVE
void Floppy::sendNull() {
  FLOPPY_SERIAL.write(pin);
  FLOPPY_SERIAL.write(nix);
  FLOPPY_SERIAL.write(nix);
}

// STEPS BETWEEN CADENCES
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

// READ INPUTS
// CHOOSING MODE
void Floppy::findMode() {
    // LEVER SWITCH #1
    if(modeOne == 1) {
      triggerCadence = true;
      triggerChaosMode = false;
      digitalWrite(11, HIGH);
      Serial.println("CADENCE ACTIVATED.");
  } else if (modeOne == 2) {
      triggerChaosMode = true;
      triggerCadence = false;
      Serial.println("CHAOS ACTIVATED.");
  }
    
  // LEVER SWITCH #2    
  if (modeTwo == 1) {
      backwards = false;
      Serial.println("BACKWARDS ACTIVATED.");
  } else if (modeTwo == 2) {
      backwards = true;
      Serial.println("BACKWARDS DEACTIVATED.");
  }
    
  // LEVER SWITCH #3
  if (modeThree == 1) {
      triggerJazzy = true;
      blueNote = true;
      Serial.println("JAZZY ACTIVATED.");
  } else if (modeThree == 2) {
      triggerJazzy = false;
      blueNote = false;
      Serial.println("JAZZY DEACTIVATED.");
  }
    
    
// PUSH-BUTTON #1
if (!turnOne) {    
    if (statusOne == 1) {
        improvisation = true;
        digitalWrite(5, HIGH);
        Serial.println("IMPROVISATION ACTIVATED.");
    }
    
    turnOne = true;
} else {
    if (statusOne == 1) {
        improvisation = false;
        digitalWrite(5, LOW);
        Serial.println("IMPROVISATION DEACTIVATED.");
    }
    
    turnOne = false;
}
    
// PUSH-BUTTON #2
if (!turnTwo) {    
    if (statusTwo == 1) {
        triggerOneNote = true;
        digitalWrite(11, HIGH);
        Serial.println("ONE NOTE ACTIVATED.");
    }
    
    turnTwo = true;
} else {
    if (statusTwo == 1) {
        triggerOneNote = false;
        digitalWrite(11, LOW);
        Serial.println("ONE NOTE DEACTIVATED.");
    }
    
    turnTwo = false;
}
    
// PUSH-BUTTON #3
if (!turnThree) {    
    if (statusThree == 1) {
        triggerChromatic = true;
        digitalWrite(12, HIGH);
        Serial.println("CHROMATIC ACTIVATED.");
    }
    
    turnThree = true;
} else {
    if (statusThree == 1) {
        triggerChromatic = false;
        digitalWrite(12, LOW);
        Serial.println("CHROMATIC DEACTIVATED.");
    }
    
    turnThree = false;
}
    
// PUSH-BUTTON #4    
if (!turnFour) {    
    if (statusFour == 1) {
        minor = true;
        digitalWrite(5, HIGH);
        digitalWrite(12, HIGH);
        Serial.println("MINOR ACTIVATED.");
    }
    
    turnFour = true;
} else {
    if (statusFour == 1) {
        minor = false;
        digitalWrite(5, LOW);
        digitalWrite(12, LOW);
        Serial.println("MINOR DEACTIVATED.");
    }
    
    turnFour = false;
}
 
// GENERATE MESSAGE
 message = generateMIDI();
}