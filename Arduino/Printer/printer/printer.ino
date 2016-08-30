/*************************************************


  ==== 1970 ====

  PRINTER RECEIVER: PRINTER.INO
  KENO WESTHOFF
  HOCHSCHULE FÜR KÜNSTE BREMEN
  2016


*************************************************/



// INCLUDE TIMER LIBRARY
#include <Timer.h>


// INITIALISE TIMER
Timer t;


// PRINTER PINS
const int d0 = 4;
const int d1 = 5;
const int d2 = 6;
const int d3 = 7;
const int d4 = 8;
const int d5 = 9;
const int d6 = 10;
const int d7 = 11;
const int strobe = 12;
const int autofd = 13;

byte n0;
byte n1;
byte n2;
byte n3;
byte n4;
byte n5;
byte n6;
byte n7;
byte strobeNumber;
byte autofdNumber;

byte message;
int globalCount;

bool wrong = false;


/*************************************************
  SETUP()
  SETTING UP PINS AND SERIAL COMMUNICATION
  INPUT: NONE
  OUTPUT: NONE
*************************************************/

void setup() {

  // SETTING UP PINS
  pinMode(d0, OUTPUT);
  pinMode(d1, OUTPUT);
  pinMode(d2, OUTPUT);
  pinMode(d3, OUTPUT);
  pinMode(d4, OUTPUT);
  pinMode(d5, OUTPUT);
  pinMode(d6, OUTPUT);
  pinMode(d7, OUTPUT);
  pinMode(strobe, OUTPUT);
  pinMode(autofd, OUTPUT);

  // SETTING UP SERIAL COMMUNICATION
  Serial.begin(9600);

  t.every(1000, playNull);
  t.every(1500, funnyThing);
  t.every(2500, trololo);
  t.every(60, doIt);
}



/*************************************************
  LOOP()
  READING MESSAGE AND TRIGGERING COMPOSITION
  INPUT: NONE
  OUTPUT: NONE
*************************************************/

void loop() {
  if (Serial.available() > 0) {
    const int factor = 12;
    
    message = Serial.read();
    digitalWrite(13, HIGH);

    if(wrong)
    {
      delay (0);
    }
    
    if (message > 120)
    {
       delay(message * factor);
       wrong = false;
    }
    else if (message > 40 && message < 60) {
      delay(message * message);
      wrong = false;
    }
    else
    {
      delay(10);
      wrong = true;
    }
  }

  /*n0 = message & 512;
    n1 = message & 256;
    n2 = message & 128;
    n3 = message & 64;
    n4 = message & 32;
    n5 = message & 16;
    n6 = message & 8;
    n7 = message & 4;
    strobeNumber = 1;
    autofdNumber = message & 1;*/

  /*n0 = message[0];
    n1 = message[1];
    n2 = message[2];
    n3 = message[3];
    n4 = message[4];
    n5 = message[5];
    n6 = message[6];
    n7 = message[7];
    strobeNumber = 1;
    autofdNumber = message[9];*/
  strobeNumber = 1;
  autofdNumber = 0;

  Serial.println(message);

  if (message == 44) {
    designer();
    Serial.println("DESIGNER ACTIVATED.");
  }

  if ( globalCount == 2 ) {
    for (int i = 0; i < 10; i++) {
      if (message > 25) {
        dance();
        delay(2);
        Serial.println("DANCE ACTIVATED.");
      } else  {
        infinity();
        delay(2);
        Serial.println("INFINITY ACTIVATED.");
      }
    }
    if (message < 45) {
      t.every(500, playGrafikBeat);
      t.every(750, designer);
      t.every(625, doIt);
      delay(2);
      Serial.println("GRAFIK-BEAT ACTIVATED.");
    } else {
      t.every(100, doIt);
      t.every(250, dance);
      delay(2);
      Serial.println("DO IT ACTIVATED.");
    }
  }

  if (message == 0) {
    t.every(10000, playNull);
  }

  if (globalCount == 5 && message > 50) {
    t.every(50, goingCrazy);
    t.every(1125, dance);
    t.every(10000, infinity);
    Serial.println("GOING CRAZY ACTIVATED.");
    delay(2);
  }

  if (globalCount == 2 && message > 100) {
    t.every(200, funnyThing);
    t.every(100000, playNull);
  }

  if (message > 120) {
    over();
    t.every(1000, dance);
  }

  if (globalCount > 10) {
    globalCount = 0;
    trololo();
  }

  globalCount++;
  delay(message * 10);

  // UPDATE TIMER
  t.update();
}

void playGrafikBeat() {
  // ESC

  if (message > 35) {
    digitalWrite(d0, LOW);
    digitalWrite(d1, HIGH);
    digitalWrite(d2, LOW);
    digitalWrite(d3, HIGH);
    digitalWrite(d4, HIGH);
    digitalWrite(d5, LOW);
    digitalWrite(d6, LOW);
    digitalWrite(d7, HIGH);
    digitalWrite(strobe, LOW);

    delay(10);

    digitalWrite(strobe, HIGH);
    digitalWrite(d0, LOW);
    digitalWrite(d1, LOW);
    digitalWrite(d2, LOW);
    digitalWrite(d3, LOW);
    digitalWrite(d4, LOW);
    digitalWrite(d5, LOW);
    digitalWrite(d6, LOW);
    digitalWrite(d7, LOW);

    delay(10);
  }

  digitalWrite(d0, LOW);
  digitalWrite(d1, LOW);
  digitalWrite(d2, LOW);
  digitalWrite(d3, HIGH);
  digitalWrite(d4, HIGH);
  digitalWrite(d5, LOW);
  digitalWrite(d6, HIGH);
  digitalWrite(d7, HIGH);
  digitalWrite(strobe, LOW);

  delay(10);

  digitalWrite(strobe, HIGH);
  digitalWrite(d0, LOW);
  digitalWrite(d1, LOW);
  digitalWrite(d2, LOW);
  digitalWrite(d3, LOW);
  digitalWrite(d4, LOW);
  digitalWrite(d5, LOW);
  digitalWrite(d6, LOW);
  digitalWrite(d7, LOW);

  delay(10);


  // K
  digitalWrite(d0, LOW);
  digitalWrite(d1, HIGH);
  digitalWrite(d2, LOW);
  digitalWrite(d3, LOW);
  digitalWrite(d4, HIGH);
  digitalWrite(d5, LOW);
  digitalWrite(d6, HIGH);
  digitalWrite(d7, HIGH);
  digitalWrite(strobe, LOW);

  delay(10);

  digitalWrite(strobe, HIGH);
  digitalWrite(d0, LOW);
  digitalWrite(d1, LOW);
  digitalWrite(d2, LOW);
  digitalWrite(d3, LOW);
  digitalWrite(d4, LOW);
  digitalWrite(d5, LOW);
  digitalWrite(d6, LOW);
  digitalWrite(d7, LOW);

  delay(10);


  // 1
  digitalWrite(d0, LOW);
  digitalWrite(d1, LOW);
  digitalWrite(d2, LOW);
  digitalWrite(d3, HIGH);
  digitalWrite(d4, LOW);
  digitalWrite(d5, LOW);
  digitalWrite(d6, HIGH);
  digitalWrite(d7, LOW);
  digitalWrite(strobe, LOW);

  delay(10);

  digitalWrite(strobe, HIGH);
  digitalWrite(d0, LOW);
  digitalWrite(d1, LOW);
  digitalWrite(d2, LOW);
  digitalWrite(d3, LOW);
  digitalWrite(d4, LOW);
  digitalWrite(d5, LOW);
  digitalWrite(d6, LOW);
  digitalWrite(d7, LOW);

  delay(10);


  // 0
  digitalWrite(d0, LOW);
  digitalWrite(d1, LOW);
  digitalWrite(d2, LOW);
  digitalWrite(d3, LOW);
  digitalWrite(d4, LOW);
  digitalWrite(d5, LOW);
  digitalWrite(d6, LOW);
  digitalWrite(d7, LOW);
  digitalWrite(strobe, LOW);

  delay(10);

  digitalWrite(strobe, HIGH);
  digitalWrite(d0, LOW);
  digitalWrite(d1, LOW);
  digitalWrite(d2, LOW);
  digitalWrite(d3, LOW);
  digitalWrite(d4, LOW);
  digitalWrite(d5, LOW);
  digitalWrite(d6, LOW);
  digitalWrite(d7, LOW);

  delay(10);
}

void doIt() {
  digitalWrite(d0, LOW);
  digitalWrite(d1, HIGH);
  digitalWrite(d2, HIGH);
  digitalWrite(d3, HIGH);
  digitalWrite(d4, LOW);
  digitalWrite(d5, LOW);
  digitalWrite(d6, LOW);
  digitalWrite(d7, LOW);
  digitalWrite(strobe, LOW);

  delay(10);

  digitalWrite(strobe, HIGH);
  digitalWrite(d0, LOW);
  digitalWrite(d1, LOW);
  digitalWrite(d2, LOW);
  digitalWrite(d3, LOW);
  digitalWrite(d4, LOW);
  digitalWrite(d5, LOW);
  digitalWrite(d6, LOW);
  digitalWrite(d7, LOW);
}

void dance() {
  // ESC
  digitalWrite(d0, LOW);
  digitalWrite(d1, LOW);
  digitalWrite(d2, LOW);
  digitalWrite(d3, HIGH);
  digitalWrite(d4, HIGH);
  digitalWrite(d5, LOW);
  digitalWrite(d6, HIGH);
  digitalWrite(d7, HIGH);
  digitalWrite(strobe, LOW);

  delay(10);

  digitalWrite(strobe, HIGH);
  digitalWrite(d0, LOW);
  digitalWrite(d1, LOW);
  digitalWrite(d2, LOW);
  digitalWrite(d3, LOW);
  digitalWrite(d4, LOW);
  digitalWrite(d5, LOW);
  digitalWrite(d6, LOW);
  digitalWrite(d7, LOW);

  delay(10);


  // K
  digitalWrite(d0, LOW);
  digitalWrite(d1, HIGH);
  digitalWrite(d2, LOW);
  digitalWrite(d3, LOW);
  digitalWrite(d4, HIGH);
  digitalWrite(d5, LOW);
  digitalWrite(d6, HIGH);
  digitalWrite(d7, HIGH);
  digitalWrite(strobe, LOW);

  delay(10);

  digitalWrite(strobe, HIGH);
  digitalWrite(d0, LOW);
  digitalWrite(d1, LOW);
  digitalWrite(d2, LOW);
  digitalWrite(d3, LOW);
  digitalWrite(d4, LOW);
  digitalWrite(d5, LOW);
  digitalWrite(d6, LOW);
  digitalWrite(d7, LOW);

  delay(10);


  // 161
  digitalWrite(d0, LOW);
  digitalWrite(d1, LOW);
  digitalWrite(d2, LOW);
  digitalWrite(d3, LOW);
  digitalWrite(d4, LOW);
  digitalWrite(d5, LOW);
  digitalWrite(d6, LOW);
  digitalWrite(d7, HIGH);
  digitalWrite(strobe, LOW);

  delay(10);

  digitalWrite(strobe, HIGH);
  digitalWrite(d0, LOW);
  digitalWrite(d1, LOW);
  digitalWrite(d2, LOW);
  digitalWrite(d3, LOW);
  digitalWrite(d4, LOW);
  digitalWrite(d5, LOW);
  digitalWrite(d6, LOW);
  digitalWrite(d7, LOW);

  delay(10);


  // 0
  digitalWrite(d0, LOW);
  digitalWrite(d1, LOW);
  digitalWrite(d2, LOW);
  digitalWrite(d3, LOW);
  digitalWrite(d4, LOW);
  digitalWrite(d5, LOW);
  digitalWrite(d6, LOW);
  digitalWrite(d7, LOW);
  digitalWrite(strobe, LOW);

  delay(10);

  digitalWrite(strobe, HIGH);
  digitalWrite(d0, LOW);
  digitalWrite(d1, LOW);
  digitalWrite(d2, LOW);
  digitalWrite(d3, LOW);
  digitalWrite(d4, LOW);
  digitalWrite(d5, LOW);
  digitalWrite(d6, LOW);
  digitalWrite(d7, LOW);

  delay(10);
}

void infinity() {
  //HELLER BLOCK
  Serial.println("Heller Block");
  digitalWrite(d0, HIGH);
  digitalWrite(d1, LOW);
  digitalWrite(d2, HIGH);
  digitalWrite(d3, HIGH);
  digitalWrite(d4, LOW);
  digitalWrite(d5, LOW);
  digitalWrite(d6, LOW);
  digitalWrite(d7, LOW);
  digitalWrite(strobe, LOW);


  digitalWrite(strobe, HIGH);
  digitalWrite(d0, LOW);
  digitalWrite(d1, LOW);
  digitalWrite(d2, LOW);
  digitalWrite(d3, LOW);
  digitalWrite(d4, LOW);
  digitalWrite(d5, LOW);
  digitalWrite(d6, LOW);
  digitalWrite(d7, LOW);
}

void designer() {

  digitalWrite(d0, LOW);
  digitalWrite(d1, HIGH);
  digitalWrite(d2, LOW);
  digitalWrite(d3, LOW);
  digitalWrite(d4, LOW);
  digitalWrite(d5, HIGH);
  digitalWrite(d6, LOW);
  digitalWrite(d7, LOW);
  digitalWrite(strobe, LOW);

  delay(1);

  digitalWrite(strobe, HIGH);
  digitalWrite(d0, LOW);
  digitalWrite(d1, LOW);
  digitalWrite(d2, LOW);
  digitalWrite(d3, LOW);
  digitalWrite(d4, LOW);
  digitalWrite(d5, LOW);
  digitalWrite(d6, LOW);
  digitalWrite(d7, LOW);

  delay(1);

  digitalWrite(d0, LOW);
  digitalWrite(d1, HIGH);
  digitalWrite(d2, LOW);
  digitalWrite(d3, HIGH);
  digitalWrite(d4, LOW);
  digitalWrite(d5, HIGH);
  digitalWrite(d6, LOW);
  digitalWrite(d7, HIGH);
  digitalWrite(strobe, LOW);

  delay(1);

  digitalWrite(strobe, HIGH);
  digitalWrite(d0, LOW);
  digitalWrite(d1, LOW);
  digitalWrite(d2, LOW);
  digitalWrite(d3, LOW);
  digitalWrite(d4, LOW);
  digitalWrite(d5, LOW);
  digitalWrite(d6, LOW);
  digitalWrite(d7, LOW);

  delay(1);

  digitalWrite(d0, LOW);
  digitalWrite(d1, LOW);
  digitalWrite(d2, HIGH);
  digitalWrite(d3, LOW);
  digitalWrite(d4, LOW);
  digitalWrite(d5, LOW);
  digitalWrite(d6, LOW);
  digitalWrite(d7, LOW);
  digitalWrite(strobe, LOW);

  delay(1);

  digitalWrite(strobe, HIGH);
  digitalWrite(d0, LOW);
  digitalWrite(d1, LOW);
  digitalWrite(d2, LOW);
  digitalWrite(d3, LOW);
  digitalWrite(d4, LOW);
  digitalWrite(d5, LOW);
  digitalWrite(d6, LOW);
  digitalWrite(d7, LOW);

  delay(1);

  digitalWrite(d0, LOW);
  digitalWrite(d1, HIGH);
  digitalWrite(d2, LOW);
  digitalWrite(d3, LOW);
  digitalWrite(d4, LOW);
  digitalWrite(d5, LOW);
  digitalWrite(d6, HIGH);
  digitalWrite(d7, LOW);
  digitalWrite(strobe, LOW);

  delay(1);

  digitalWrite(strobe, HIGH);
  digitalWrite(d0, LOW);
  digitalWrite(d1, LOW);
  digitalWrite(d2, LOW);
  digitalWrite(d3, LOW);
  digitalWrite(d4, LOW);
  digitalWrite(d5, LOW);
  digitalWrite(d6, LOW);
  digitalWrite(d7, LOW);

  delay(1);

  digitalWrite(d0, LOW);
  digitalWrite(d1, HIGH);
  digitalWrite(d2, LOW);
  digitalWrite(d3, LOW);
  digitalWrite(d4, HIGH);
  digitalWrite(d5, LOW);
  digitalWrite(d6, LOW);
  digitalWrite(d7, HIGH);
  digitalWrite(strobe, LOW);

  delay(1);

  digitalWrite(strobe, HIGH);
  digitalWrite(d0, LOW);
  digitalWrite(d1, LOW);
  digitalWrite(d2, LOW);
  digitalWrite(d3, LOW);
  digitalWrite(d4, LOW);
  digitalWrite(d5, LOW);
  digitalWrite(d6, LOW);
  digitalWrite(d7, LOW);

  delay(1);

  digitalWrite(d0, LOW);
  digitalWrite(d1, HIGH);
  digitalWrite(d2, LOW);
  digitalWrite(d3, HIGH);
  digitalWrite(d4, LOW);
  digitalWrite(d5, LOW);
  digitalWrite(d6, HIGH);
  digitalWrite(d7, HIGH);
  digitalWrite(strobe, LOW);

  delay(1);

  digitalWrite(strobe, HIGH);
  digitalWrite(d0, LOW);
  digitalWrite(d1, LOW);
  digitalWrite(d2, LOW);
  digitalWrite(d3, LOW);
  digitalWrite(d4, LOW);
  digitalWrite(d5, LOW);
  digitalWrite(d6, LOW);
  digitalWrite(d7, LOW);

  delay(1);

  digitalWrite(d0, LOW);
  digitalWrite(d1, HIGH);
  digitalWrite(d2, LOW);
  digitalWrite(d3, HIGH);
  digitalWrite(d4, LOW);
  digitalWrite(d5, HIGH);
  digitalWrite(d6, LOW);
  digitalWrite(d7, LOW);
  digitalWrite(strobe, LOW);

  delay(1);

  digitalWrite(strobe, HIGH);
  digitalWrite(d0, LOW);
  digitalWrite(d1, LOW);
  digitalWrite(d2, LOW);
  digitalWrite(d3, LOW);
  digitalWrite(d4, LOW);
  digitalWrite(d5, LOW);
  digitalWrite(d6, LOW);
  digitalWrite(d7, LOW);

  delay(1);

  digitalWrite(d0, LOW);
  digitalWrite(d1, LOW);
  digitalWrite(d2, HIGH);
  digitalWrite(d3, LOW);
  digitalWrite(d4, LOW);
  digitalWrite(d5, LOW);
  digitalWrite(d6, LOW);
  digitalWrite(d7, LOW);
  digitalWrite(strobe, LOW);

  delay(1);

  digitalWrite(strobe, HIGH);
  digitalWrite(d0, LOW);
  digitalWrite(d1, LOW);
  digitalWrite(d2, LOW);
  digitalWrite(d3, LOW);
  digitalWrite(d4, LOW);
  digitalWrite(d5, LOW);
  digitalWrite(d6, LOW);
  digitalWrite(d7, LOW);

  delay(1);

  digitalWrite(d0, LOW);
  digitalWrite(d1, HIGH);
  digitalWrite(d2, LOW);
  digitalWrite(d3, LOW);
  digitalWrite(d4, LOW);
  digitalWrite(d5, HIGH);
  digitalWrite(d6, LOW);
  digitalWrite(d7, LOW);
  digitalWrite(strobe, LOW);

  delay(1);

  digitalWrite(strobe, HIGH);
  digitalWrite(d0, LOW);
  digitalWrite(d1, LOW);
  digitalWrite(d2, LOW);
  digitalWrite(d3, LOW);
  digitalWrite(d4, LOW);
  digitalWrite(d5, LOW);
  digitalWrite(d6, LOW);
  digitalWrite(d7, LOW);

  delay(1);

  digitalWrite(d0, LOW);
  digitalWrite(d1, HIGH);
  digitalWrite(d2, LOW);
  digitalWrite(d3, LOW);
  digitalWrite(d4, LOW);
  digitalWrite(d5, HIGH);
  digitalWrite(d6, LOW);
  digitalWrite(d7, HIGH);
  digitalWrite(strobe, LOW);

  delay(1);

  digitalWrite(strobe, HIGH);
  digitalWrite(d0, LOW);
  digitalWrite(d1, LOW);
  digitalWrite(d2, LOW);
  digitalWrite(d3, LOW);
  digitalWrite(d4, LOW);
  digitalWrite(d5, LOW);
  digitalWrite(d6, LOW);
  digitalWrite(d7, LOW);

  delay(1);

  digitalWrite(d0, LOW);
  digitalWrite(d1, HIGH);
  digitalWrite(d2, LOW);
  digitalWrite(d3, HIGH);
  digitalWrite(d4, LOW);
  digitalWrite(d5, LOW);
  digitalWrite(d6, HIGH);
  digitalWrite(d7, HIGH);
  digitalWrite(strobe, LOW);

  delay(1);

  digitalWrite(strobe, HIGH);
  digitalWrite(d0, LOW);
  digitalWrite(d1, LOW);
  digitalWrite(d2, LOW);
  digitalWrite(d3, LOW);
  digitalWrite(d4, LOW);
  digitalWrite(d5, LOW);
  digitalWrite(d6, LOW);
  digitalWrite(d7, LOW);

  delay(1);

  digitalWrite(d0, LOW);
  digitalWrite(d1, HIGH);
  digitalWrite(d2, LOW);
  digitalWrite(d3, LOW);
  digitalWrite(d4, HIGH);
  digitalWrite(d5, LOW);
  digitalWrite(d6, LOW);
  digitalWrite(d7, HIGH);
  digitalWrite(strobe, LOW);

  delay(1);

  digitalWrite(strobe, HIGH);
  digitalWrite(d0, LOW);
  digitalWrite(d1, LOW);
  digitalWrite(d2, LOW);
  digitalWrite(d3, LOW);
  digitalWrite(d4, LOW);
  digitalWrite(d5, LOW);
  digitalWrite(d6, LOW);
  digitalWrite(d7, LOW);

  delay(1);

  digitalWrite(d0, LOW);
  digitalWrite(d1, HIGH);
  digitalWrite(d2, LOW);
  digitalWrite(d3, LOW);
  digitalWrite(d4, LOW);
  digitalWrite(d5, HIGH);
  digitalWrite(d6, HIGH);
  digitalWrite(d7, HIGH);
  digitalWrite(strobe, LOW);

  delay(1);

  digitalWrite(strobe, HIGH);
  digitalWrite(d0, LOW);
  digitalWrite(d1, LOW);
  digitalWrite(d2, LOW);
  digitalWrite(d3, LOW);
  digitalWrite(d4, LOW);
  digitalWrite(d5, LOW);
  digitalWrite(d6, LOW);
  digitalWrite(d7, LOW);

  delay(1);

  digitalWrite(d0, LOW);
  digitalWrite(d1, HIGH);
  digitalWrite(d2, LOW);
  digitalWrite(d3, LOW);
  digitalWrite(d4, HIGH);
  digitalWrite(d5, HIGH);
  digitalWrite(d6, HIGH);
  digitalWrite(d7, LOW);
  digitalWrite(strobe, LOW);

  delay(1);

  digitalWrite(strobe, HIGH);
  digitalWrite(d0, LOW);
  digitalWrite(d1, LOW);
  digitalWrite(d2, LOW);
  digitalWrite(d3, LOW);
  digitalWrite(d4, LOW);
  digitalWrite(d5, LOW);
  digitalWrite(d6, LOW);
  digitalWrite(d7, LOW);

  delay(1);


  digitalWrite(d0, LOW);
  digitalWrite(d1, HIGH);
  digitalWrite(d2, LOW);
  digitalWrite(d3, LOW);
  digitalWrite(d4, LOW);
  digitalWrite(d5, HIGH);
  digitalWrite(d6, LOW);
  digitalWrite(d7, HIGH);
  digitalWrite(strobe, LOW);

  delay(1);

  digitalWrite(strobe, HIGH);
  digitalWrite(d0, LOW);
  digitalWrite(d1, LOW);
  digitalWrite(d2, LOW);
  digitalWrite(d3, LOW);
  digitalWrite(d4, LOW);
  digitalWrite(d5, LOW);
  digitalWrite(d6, LOW);
  digitalWrite(d7, LOW);

  delay(1);

  digitalWrite(d0, LOW);
  digitalWrite(d1, HIGH);
  digitalWrite(d2, LOW);
  digitalWrite(d3, HIGH);
  digitalWrite(d4, LOW);
  digitalWrite(d5, LOW);
  digitalWrite(d6, HIGH);
  digitalWrite(d7, LOW);
  digitalWrite(strobe, LOW);

  delay(1);

  digitalWrite(strobe, HIGH);
  digitalWrite(d0, LOW);
  digitalWrite(d1, LOW);
  digitalWrite(d2, LOW);
  digitalWrite(d3, LOW);
  digitalWrite(d4, LOW);
  digitalWrite(d5, LOW);
  digitalWrite(d6, LOW);
  digitalWrite(d7, LOW);

  delay(1);

  digitalWrite(d0, LOW);
  digitalWrite(d1, LOW);
  digitalWrite(d2, HIGH);
  digitalWrite(d3, LOW);
  digitalWrite(d4, LOW);
  digitalWrite(d5, LOW);
  digitalWrite(d6, LOW);
  digitalWrite(d7, LOW);
  digitalWrite(strobe, LOW);

  delay(1);

  digitalWrite(strobe, HIGH);
  digitalWrite(d0, LOW);
  digitalWrite(d1, LOW);
  digitalWrite(d2, LOW);
  digitalWrite(d3, LOW);
  digitalWrite(d4, LOW);
  digitalWrite(d5, LOW);
  digitalWrite(d6, LOW);
  digitalWrite(d7, LOW);

  delay(1);
}

void goingCrazy() {
  // ESC
  digitalWrite(d0, LOW);
  digitalWrite(d1, LOW);
  digitalWrite(d2, LOW);
  digitalWrite(d3, HIGH);
  digitalWrite(d4, HIGH);
  digitalWrite(d5, LOW);
  digitalWrite(d6, HIGH);
  digitalWrite(d7, HIGH);
  digitalWrite(strobe, LOW);

  delay(2);

  digitalWrite(strobe, HIGH);
  digitalWrite(d0, LOW);
  digitalWrite(d1, LOW);
  digitalWrite(d2, LOW);
  digitalWrite(d3, LOW);
  digitalWrite(d4, LOW);
  digitalWrite(d5, LOW);
  digitalWrite(d6, LOW);
  digitalWrite(d7, LOW);


  // W
  digitalWrite(d0, LOW);
  digitalWrite(d1, HIGH);
  digitalWrite(d2, LOW);
  digitalWrite(d3, HIGH);
  digitalWrite(d4, LOW);
  digitalWrite(d5, HIGH);
  digitalWrite(d6, HIGH);
  digitalWrite(d7, HIGH);
  digitalWrite(strobe, LOW);

  delay(2);

  digitalWrite(strobe, HIGH);
  digitalWrite(d0, LOW);
  digitalWrite(d1, LOW);
  digitalWrite(d2, LOW);
  digitalWrite(d3, LOW);
  digitalWrite(d4, LOW);
  digitalWrite(d5, LOW);
  digitalWrite(d6, LOW);
  digitalWrite(d7, LOW);

  // 0
  digitalWrite(d0, LOW);
  digitalWrite(d1, LOW);
  digitalWrite(d2, HIGH);
  digitalWrite(d3, HIGH);
  digitalWrite(d4, LOW);
  digitalWrite(d5, LOW);
  digitalWrite(d6, LOW);
  digitalWrite(d7, LOW);
  digitalWrite(strobe, LOW);

  delay(2);

  digitalWrite(strobe, HIGH);
  digitalWrite(d0, LOW);
  digitalWrite(d1, LOW);
  digitalWrite(d2, LOW);
  digitalWrite(d3, LOW);
  digitalWrite(d4, LOW);
  digitalWrite(d5, LOW);
  digitalWrite(d6, LOW);
  digitalWrite(d7, LOW);

  //!
  digitalWrite(d0, LOW);
  digitalWrite(d1, LOW);
  digitalWrite(d2, HIGH);
  digitalWrite(d3, LOW);
  digitalWrite(d4, LOW);
  digitalWrite(d5, LOW);
  digitalWrite(d6, LOW);
  digitalWrite(d7, HIGH);
  digitalWrite(strobe, LOW);

  delay(2);

  digitalWrite(strobe, HIGH);
  digitalWrite(d0, LOW);
  digitalWrite(d1, LOW);
  digitalWrite(d2, LOW);
  digitalWrite(d3, LOW);
  digitalWrite(d4, LOW);
  digitalWrite(d5, LOW);
  digitalWrite(d6, LOW);
  digitalWrite(d7, LOW);

  // ESC
  digitalWrite(d0, LOW);
  digitalWrite(d1, LOW);
  digitalWrite(d2, LOW);
  digitalWrite(d3, HIGH);
  digitalWrite(d4, HIGH);
  digitalWrite(d5, LOW);
  digitalWrite(d6, HIGH);
  digitalWrite(d7, HIGH);
  digitalWrite(strobe, LOW);

  delay(2);

  digitalWrite(strobe, HIGH);
  digitalWrite(d0, LOW);
  digitalWrite(d1, LOW);
  digitalWrite(d2, LOW);
  digitalWrite(d3, LOW);
  digitalWrite(d4, LOW);
  digitalWrite(d5, LOW);
  digitalWrite(d6, LOW);
  digitalWrite(d7, LOW);


  // J
  digitalWrite(d0, LOW);
  digitalWrite(d1, HIGH);
  digitalWrite(d2, LOW);
  digitalWrite(d3, LOW);
  digitalWrite(d4, HIGH);
  digitalWrite(d5, LOW);
  digitalWrite(d6, HIGH);
  digitalWrite(d7, LOW);
  digitalWrite(strobe, LOW);

  delay(2);

  digitalWrite(strobe, HIGH);
  digitalWrite(d0, LOW);
  digitalWrite(d1, LOW);
  digitalWrite(d2, LOW);
  digitalWrite(d3, LOW);
  digitalWrite(d4, LOW);
  digitalWrite(d5, LOW);
  digitalWrite(d6, LOW);
  digitalWrite(d7, LOW);

  // 9
  digitalWrite(d0, LOW);
  digitalWrite(d1, LOW);
  digitalWrite(d2, HIGH);
  digitalWrite(d3, HIGH);
  digitalWrite(d4, HIGH);
  digitalWrite(d5, LOW);
  digitalWrite(d6, LOW);
  digitalWrite(d7, HIGH);
  digitalWrite(strobe, LOW);

  digitalWrite(strobe, HIGH);
  digitalWrite(d0, LOW);
  digitalWrite(d1, LOW);
  digitalWrite(d2, LOW);
  digitalWrite(d3, LOW);
  digitalWrite(d4, LOW);
  digitalWrite(d5, LOW);
  digitalWrite(d6, LOW);
  digitalWrite(d7, LOW);

  delay(globalCount * PI);
}

void playNull() {
  // 9
  digitalWrite(d0, LOW);
  digitalWrite(d1, HIGH);
  digitalWrite(d2, HIGH);
  digitalWrite(d3, HIGH);
  digitalWrite(d4, HIGH);
  digitalWrite(d5, LOW);
  digitalWrite(d6, HIGH);
  digitalWrite(d7, HIGH);
  digitalWrite(strobe, LOW);

  digitalWrite(strobe, HIGH);
  digitalWrite(d0, LOW);
  digitalWrite(d1, LOW);
  digitalWrite(d2, LOW);
  digitalWrite(d3, LOW);
  digitalWrite(d4, LOW);
  digitalWrite(d5, LOW);
  digitalWrite(d6, LOW);
  digitalWrite(d7, LOW);
}

void trololo() {
  Serial.println("TROLOLO");
  // 9
  digitalWrite(d0, LOW);
  digitalWrite(d1, HIGH);
  digitalWrite(d2, HIGH);
  digitalWrite(d3, LOW);
  digitalWrite(d4, HIGH);
  digitalWrite(d5, LOW);
  digitalWrite(d6, HIGH);
  digitalWrite(d7, LOW);
  digitalWrite(strobe, LOW);

  digitalWrite(strobe, HIGH);
  digitalWrite(d0, LOW);
  digitalWrite(d1, LOW);
  digitalWrite(d2, LOW);
  digitalWrite(d3, LOW);
  digitalWrite(d4, LOW);
  digitalWrite(d5, LOW);
  digitalWrite(d6, LOW);
  digitalWrite(d7, LOW);

  digitalWrite(d0, HIGH);
  digitalWrite(d1, HIGH);
  digitalWrite(d2, HIGH);
  digitalWrite(d3, LOW);
  digitalWrite(d4, HIGH);
  digitalWrite(d5, HIGH);
  digitalWrite(d6, LOW);
  digitalWrite(d7, HIGH);
  digitalWrite(strobe, LOW);

  digitalWrite(strobe, HIGH);
  digitalWrite(d0, LOW);
  digitalWrite(d1, LOW);
  digitalWrite(d2, LOW);
  digitalWrite(d3, LOW);
  digitalWrite(d4, LOW);
  digitalWrite(d5, LOW);
  digitalWrite(d6, LOW);
  digitalWrite(d7, LOW);

  goingCrazy();
}

void over() {
  Serial.println("OVER");
  // ESC
  digitalWrite(d0, HIGH);
  digitalWrite(d1, LOW);
  digitalWrite(d2, LOW);
  digitalWrite(d3, HIGH);
  digitalWrite(d4, HIGH);
  digitalWrite(d5, LOW);
  digitalWrite(d6, HIGH);
  digitalWrite(d7, HIGH);
  digitalWrite(strobe, LOW);

  delay(2);

  digitalWrite(strobe, HIGH);
  digitalWrite(d0, LOW);
  digitalWrite(d1, LOW);
  digitalWrite(d2, LOW);
  digitalWrite(d3, LOW);
  digitalWrite(d4, LOW);
  digitalWrite(d5, LOW);
  digitalWrite(d6, LOW);
  digitalWrite(d7, LOW);


  // J
  digitalWrite(d0, LOW);
  digitalWrite(d1, HIGH);
  digitalWrite(d2, LOW);
  digitalWrite(d3, LOW);
  digitalWrite(d4, HIGH);
  digitalWrite(d5, LOW);
  digitalWrite(d6, HIGH);
  digitalWrite(d7, LOW);

  digitalWrite(strobe, HIGH);
  digitalWrite(d0, LOW);
  digitalWrite(d1, LOW);
  digitalWrite(d2, LOW);
  digitalWrite(d3, LOW);
  digitalWrite(d4, LOW);
  digitalWrite(d5, LOW);
  digitalWrite(d6, LOW);
  digitalWrite(d7, LOW);


  // J
  digitalWrite(d0, LOW);
  digitalWrite(d1, HIGH);
  digitalWrite(d2, LOW);
  digitalWrite(d3, LOW);
  digitalWrite(d4, HIGH);
  digitalWrite(d5, LOW);
  digitalWrite(d6, LOW);
  digitalWrite(d7, HIGH);
}

void funnyThing() {
  Serial.println("FUNNY THING");
  // ESC
  digitalWrite(d0, LOW);
  digitalWrite(d1, LOW);
  digitalWrite(d2, LOW);
  digitalWrite(d3, HIGH);
  digitalWrite(d4, HIGH);
  digitalWrite(d5, LOW);
  digitalWrite(d6, HIGH);
  digitalWrite(d7, HIGH);
  digitalWrite(strobe, LOW);

  delay(2);

  digitalWrite(strobe, HIGH);
  digitalWrite(d0, LOW);
  digitalWrite(d1, LOW);
  digitalWrite(d2, LOW);
  digitalWrite(d3, LOW);
  digitalWrite(d4, LOW);
  digitalWrite(d5, LOW);
  digitalWrite(d6, LOW);
  digitalWrite(d7, LOW);


  // W
  digitalWrite(d0, LOW);
  digitalWrite(d1, HIGH);
  digitalWrite(d2, LOW);
  digitalWrite(d3, HIGH);
  digitalWrite(d4, LOW);
  digitalWrite(d5, HIGH);
  digitalWrite(d6, HIGH);
  digitalWrite(d7, HIGH);
  digitalWrite(strobe, LOW);

  delay(2);

  digitalWrite(strobe, HIGH);
  digitalWrite(d0, LOW);
  digitalWrite(d1, LOW);
  digitalWrite(d2, LOW);
  digitalWrite(d3, LOW);
  digitalWrite(d4, LOW);
  digitalWrite(d5, LOW);
  digitalWrite(d6, LOW);
  digitalWrite(d7, LOW);

  // 0
  digitalWrite(d0, LOW);
  digitalWrite(d1, LOW);
  digitalWrite(d2, HIGH);
  digitalWrite(d3, HIGH);
  digitalWrite(d4, LOW);
  digitalWrite(d5, LOW);
  digitalWrite(d6, LOW);
  digitalWrite(d7, LOW);
  digitalWrite(strobe, LOW);

  delay(2);

  digitalWrite(strobe, HIGH);
  digitalWrite(d0, LOW);
  digitalWrite(d1, LOW);
  digitalWrite(d2, LOW);
  digitalWrite(d3, LOW);
  digitalWrite(d4, LOW);
  digitalWrite(d5, LOW);
  digitalWrite(d6, LOW);
  digitalWrite(d7, LOW);

  //!
  digitalWrite(d0, LOW);
  digitalWrite(d1, LOW);
  digitalWrite(d2, HIGH);
  digitalWrite(d3, LOW);
  digitalWrite(d4, LOW);
  digitalWrite(d5, LOW);
  digitalWrite(d6, LOW);
  digitalWrite(d7, HIGH);
  digitalWrite(strobe, LOW);

  delay(2);

  digitalWrite(strobe, HIGH);
  digitalWrite(d0, LOW);
  digitalWrite(d1, LOW);
  digitalWrite(d2, LOW);
  digitalWrite(d3, LOW);
  digitalWrite(d4, LOW);
  digitalWrite(d5, LOW);
  digitalWrite(d6, LOW);
  digitalWrite(d7, LOW);

  // ESC
  digitalWrite(d0, LOW);
  digitalWrite(d1, LOW);
  digitalWrite(d2, LOW);
  digitalWrite(d3, HIGH);
  digitalWrite(d4, HIGH);
  digitalWrite(d5, LOW);
  digitalWrite(d6, HIGH);
  digitalWrite(d7, HIGH);
  digitalWrite(strobe, LOW);

  delay(2);

  digitalWrite(strobe, HIGH);
  digitalWrite(d0, LOW);
  digitalWrite(d1, LOW);
  digitalWrite(d2, LOW);
  digitalWrite(d3, LOW);
  digitalWrite(d4, LOW);
  digitalWrite(d5, LOW);
  digitalWrite(d6, LOW);
  digitalWrite(d7, LOW);


  // J
  digitalWrite(d0, LOW);
  digitalWrite(d1, HIGH);
  digitalWrite(d2, LOW);
  digitalWrite(d3, LOW);
  digitalWrite(d4, HIGH);
  digitalWrite(d5, LOW);
  digitalWrite(d6, HIGH);
  digitalWrite(d7, LOW);
  digitalWrite(strobe, LOW);

  delay(2);

  digitalWrite(strobe, HIGH);
  digitalWrite(d0, LOW);
  digitalWrite(d1, LOW);
  digitalWrite(d2, LOW);
  digitalWrite(d3, LOW);
  digitalWrite(d4, LOW);
  digitalWrite(d5, LOW);
  digitalWrite(d6, LOW);
  digitalWrite(d7, LOW);

  // 9
  digitalWrite(d0, LOW);
  digitalWrite(d1, LOW);
  digitalWrite(d2, HIGH);
  digitalWrite(d3, HIGH);
  digitalWrite(d4, HIGH);
  digitalWrite(d5, LOW);
  digitalWrite(d6, LOW);
  digitalWrite(d7, HIGH);
  digitalWrite(strobe, LOW);

  digitalWrite(strobe, HIGH);
  digitalWrite(d0, LOW);
  digitalWrite(d1, LOW);
  digitalWrite(d2, LOW);
  digitalWrite(d3, LOW);
  digitalWrite(d4, LOW);
  digitalWrite(d5, LOW);
  digitalWrite(d6, LOW);
  digitalWrite(d7, LOW);

  delay(globalCount * PI);
}
