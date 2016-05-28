/* PRINTER RECEIVER */

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

void setup() {
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
  Serial.begin(9600);
}

void loop() {
  if (Serial.available() > 0) {
    //for(int i; i <= 9; i++) {
    message = Serial.read();
    digitalWrite(13, HIGH);
    // }
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
        delay(360);
        Serial.println("DANCE ACTIVATED.");
      } else  {
        infinity();
        delay(100);
        Serial.println("INFINITY ACTIVATED.");
      }
    }
    if (message < 45) {
      playGrafikBeat();
      delay(420);
      Serial.println("GRAFIK-BEAT ACTIVATED.");
    } else {
      doIt();
      delay(240);
      Serial.println("DO IT ACTIVATED.");
    }
  }

  if (globalCount == 5 && message > 50) {
    goingCrazy();
    Serial.println("GOING CRAZY ACTIVATED.");
    delay(1000);
  }

  if (globalCount > 10) {
    globalCount = 0;
  }

  globalCount++;
  delay(message * 10);
}

void playGrafikBeat() {
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
