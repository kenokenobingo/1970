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
    
    //findMode();

  while (device_reset == 0) {

    sendNull();
      
    delay(50);

    device_reset = 1;

    _delay_ms(500);
  }

  note = generateMIDI();
  message = (byte) note;
  PRINTER_SERIAL.write(note);

  /*playTime = generateTime();
  delayTime = generateDelay();*/
 
  //Serial.println("PRINTER MESSAGE" + message);

 /* // SEND NOTES TO PRINTER INTERFACE
    PRINTER_SERIAL.write(n0);
    PRINTER_SERIAL.write(n1);
    PRINTER_SERIAL.write(n2);
    PRINTER_SERIAL.write(n3);
    PRINTER_SERIAL.write(n4);
    PRINTER_SERIAL.write(n5);
    PRINTER_SERIAL.write(n6);
    PRINTER_SERIAL.write(n7);
    PRINTER_SERIAL.write(strobe);
    PRINTER_SERIAL.write(autofd); */
   
  /*// PRINT NOTES
    Serial.println(n0);
    Serial.println(n1);
    Serial.println(n2);
    Serial.println(n3);
    Serial.println(n4);
    Serial.println(n5);
    Serial.println(n6);
    Serial.println(n7);
    Serial.println(strobe);
    Serial.println(autofd);*/
    
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

int Printer::generateMIDI() {
  //return (int) timestamp >> 24;
if (triggerOneNote) {
    //return (int) timestamp >> 24;
    return 44;
} else if (triggerChaosMode) {
    return chaosMode();
  } else if (triggerChromatic) {
      return chroma;
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
    
  // TRIGGERING INTER      
  else if (triggerInter) 
  {
      Serial.println("FLOPPY: INTER");
      int step;
      int f = 2;
      step = (0.5 * (minutes + seconds) / 10);
      return f * days + step;
  }
    
  // TRIGGERING WEIRD    
  else if (triggerWeird) 
  {
      Serial.println("FLOPPY: WEIRD");
      if (seconds == 60 || seconds == 30 || seconds == 0 || seconds == 15 || seconds == 45) {
        return 42;
      } else {
        int root; 
        root = (int) sqrt(years + seconds + minutes + hours);
        return root;
      }
  }
    
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
  }
   return 44; 
}

/* // GENERATE DURATION OF A NOTE
float Printer::generateTime() {
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
float Printer::generateDelay() {
  float x;
    
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
bool Printer::getX() {
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
} */

// CHAOS MODE
int Printer::chaosMode() {
  return random(0, 144);
}

// SILENCE THE DRIVE
void Printer::sendNull() {
    /*n0 = 0;
    n1 = 0;
    n2 = 0;
    n3 = 0;
    n4 = 0;
    n5 = 0;
    n6 = 0;
    n7 = 0;
    strobe = 1;
    autofd = 1;
    
    PRINTER_SERIAL.write(n0);
    PRINTER_SERIAL.write(n1);
    PRINTER_SERIAL.write(n2);
    PRINTER_SERIAL.write(n3);
    PRINTER_SERIAL.write(n4);
    PRINTER_SERIAL.write(n5);
    PRINTER_SERIAL.write(n6);
    PRINTER_SERIAL.write(n7);
    PRINTER_SERIAL.write(strobe);
    PRINTER_SERIAL.write(autofd);*/
    
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

  if (!bTriggered) {
    b = timestamp >> 28;
    bTriggered = true;
  } else {
      //PICKING A VALUE
      b = b + Steps[i];
  }
}

/*void Printer::doTimeshift () {
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
}*/

/*
void Printer::findMode() {
    Serial.println("PRINTER ENTERED FINDMODE FUNKTION." );
    
    if(modeOne == 1) {
      triggerCadence = true;
      triggerChaosMode = false;
      digitalWrite(11, HIGH);
      Serial.println("PRINTER CADENCE ACTIVATED.");
  } else if (modeOne == 2) {
      triggerChaosMode = true;
      triggerCadence = false;
      Serial.println("PRINTER CHAOS ACTIVATED.");
  }
    
  if (modeTwo == 1) {
      triggerOneNote = true;
      Serial.println("PRINTER ONE NOTE ACTIVATED.");
  } else if (modeTwo == 2) {
      triggerOneNote = false;
      Serial.println("PRINTER ONE NOTE DEACTIVATED.");
  }
    
  if (modeThree == 1) {
      triggerWeird = true;
      Serial.println("PRINTER WEIRD ACTIVATED.");
  } else if (modeThree == 2) {
      triggerWeird = false;
      Serial.println("PRINTER WEIRD DEACTIVATED.");
  }
    
    

if (!turnOne) {    
    if (statusOne == 1) {
        improvisation = true;
        Serial.println("PRINTER IMPROVISATION ACTIVATED.");
    }
    
    turnOne = true;
} else {
    if (statusOne == 1) {
        improvisation = false;
        Serial.println("PRINTER IMPROVISATION DEACTIVATED.");
    }
    
    turnOne = false;
}
    
    
if (!turnTwo) {    
    if (statusTwo == 1) {
        triggerOneNote = true;
        Serial.println("PRINTER ONE NOTE ACTIVATED.");
    }
    
    turnTwo = true;
} else {
    if (statusTwo == 1) {
        triggerOneNote = false;
        Serial.println("PRINTER ONE NOTE DEACTIVATED.");
    }
    
    turnTwo = false;
}
    

if (!turnThree) {    
    if (statusThree == 1) {
        triggerChromatic = true;
        Serial.println("PRINTER CHROMATIC ACTIVATED.");
    }
    
    turnThree = true;
} else {
    if (statusThree == 1) {
        triggerChromatic = false;
        Serial.println("PRINTER CHROMATIC DEACTIVATED.");
    }
    
    turnThree = false;
}
    
if (!turnFour) {    
    if (statusFour == 1) {
        minor = true;
        Serial.println("PRINTER MINOR ACTIVATED.");
    }
    
    turnFour = true;
} else {
    if (statusFour == 1) {
        minor = false;
        Serial.println("PRINTER MINOR DEACTIVATED.");
    }
    
    turnFour = false;
}
    
 message = generateMIDI();
} */