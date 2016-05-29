#include "Tape.h"

// EXTERNAL LIBRARIES
#include <util/delay.h>

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
Tape::~Tape(){/*nothing to destruct*/}

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

    //findMode();
    
  while (device_reset == 0) {
    TAPE_SERIAL.write(reset);

    TAPE_SERIAL.write(pin);
    TAPE_SERIAL.write(nix);
    TAPE_SERIAL.write(nix);
    digitalWrite(13, LOW);

    delay(50);

    device_reset = 1;

    _delay_ms(500);
  }
    
  // GENERATE MIDI MESSAGE  
  message = generateMIDI();

  // PRINT MESSAGE IN THE CONSOLE
  Serial.println(message);

  message = message + map(valueThree, 0, 1023, -10, 10);    
  message = map(message, 0, 128, 0, 255);
  note = microPeriods[message];
  period = note / magicNumber;

  // SEND THE NESSAGE TO THE TAPE CONTROL
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

  // RE-CALCULATE TIME    
  playTime = playTime + map(valueOne, 0, 1023, -100, 100);
  delayTime = delayTime + map(valueTwo, 0, 1023, -100, 100);
     
 /* // SUSATAIN NOTE
  delay(playTime);

  // SILENCE THE DRIVE    
  sendNull();
    
  // SUSTAIN SILENCE
  delay(delayTime); */

/*
  TAPE_SERIAL.write(pin);
  TAPE_SERIAL.write(nix);
  TAPE_SERIAL.write(nix); */
    
  // INTERNAL LED OFF    
  digitalWrite(13, LOW);
}


// GENERATING PITCH
// OUTPUT: RETURNS MIDI VALUE

int Tape::generateMIDI() {
    
    // TRIGGERING CHAOS MODE
    if (triggerChaosMode) {
      Serial.println("TAPE: CHAOS");
      return chaosMode();
        
    // TRIGGERING HICK HACK        
  } else if (triggerHickHack) {
      Serial.println("TAPE: HICK HACK");
      if (seconds == 1 || seconds == 2 || seconds == 3 || seconds == 4 || seconds == 5 || seconds == 30 || seconds == 31 || seconds == 32 || seconds == 33 || seconds == 34 || seconds == 35) {
          return seconds * 2;
      } else {
          return seconds;
      }
      return 0;
        
    // TRIGGERING JUMPING VALUES    
  } else if (triggerJump) {
      Serial.println("TAPE: JUMP");
      
      int x = months * random(0, months); 
      int f = 2;
      
      return (days + x) * f;
        
    // TRIGGERING SINE MODE
  } else if (triggerSine) {
      Serial.println("TAPE: SINE");
      //return sin(seconds/minutes) * 256;
      if(!triggerModulation) {
         return abs(128 * sin(6 * seconds));
      } else {
         return abs((128 * sin(6 * seconds)) * (100 * sin(seconds/6)));
      }
        
    // TRIGGERING TANGENT MODE    
  } else if (triggerTan) {
      Serial.println("TAPE: TANGENT");
      return abs(128 * tan(6 * seconds));
        
    // TRIGGERING EXPONENTIAL MODE
  } else if (triggerLog) {
      Serial.println("TAPE: LOGARITHMIC");
      Serial.println((log(sin(seconds)) + exp(1)) * 60);    
      return (log(sin(seconds)) + exp(1)) * 60;
  } else if (triggerSqrt + months) {
        return sqrt(seconds) * 40;
  } else if (triggerEFu) {
      return exp(seconds%5);
        
    // TRIGGERING BREAK MODE
  } else if (triggerBreak) {
      Serial.println("TAPE: BREAK");
      for(int i=0; i<=seconds+months; i++) {
      return seconds * 2;
      }
      return 0;
        
    // TRIGGERING STUTTERING MODE
  } else if (triggerStutter) {
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
        
    // TRIGGERING NOTHING
  } else if (triggerNull) {
      Serial.println("TAPE: NULL");
      return 0;
        
    // TRIGGERING CHROMATIC MODE    
  } else if (triggerChromatic) {
      Serial.println("TAPE: CHROMA");
      return chroma;
        
    // TRIGGERING INTER MODE
  } else if (triggerInter) {
    Serial.println("TAPE: INTER");
    int step;
    step = seconds / 5 - minutes % 4;
    return months * days + step;
        
    // TRIGGERING WEIRD MODE
  } else if (triggerWeird) {
      Serial.println("TAPE: WEIRD");
      if (seconds < 60 && seconds > 30) {
          return 42;
      } else {
      return sqrt(years);
      }
        
    // TRIGGERING ONE NOTE MODE
  } else if (triggerOneNote) {
      Serial.println("TAPE: ONE NOTE");
    //return (int) timestamp >> 24;
    return 44;
        
    // TRIGGERING CADENCE MODE
  } else if (triggerCadence && !blueNote) {
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
        
    // TRIGGERING JAZZY MODE
  } else if (triggerCadence && blueNote) {
      Serial.println("TAPE: JAZZY");
      
      counting++;
      Serial.println(counting);
      
      if (counting > 2) {
          counting = 0;
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
  }
      
      return 190;
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

// STEPS BETWEEN CADENCES
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
/*
// READ INPUTS
// CHOOSING MODE
void Tape::findMode() {
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
} */