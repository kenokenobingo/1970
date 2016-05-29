/*************************************************


==== 1970 ====

TEENSY PROGRAM: _1970.INO
KENO WESTHOFF
HOCHSCHULE FÜR KÜNSTE BREMEN
2016


*************************************************/


#include <RTClib.h>
#include <Wire.h>

#include <Floppy.h>
#include <Printer.h>
#include <Tape.h>

Floppy floppy;
Printer printer;
Tape tape;
//RTC_DS1307 RTC;
RTC_Millis RTC;
int nowTime;

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

void setup() {
  Serial.begin(9600);
  Wire.begin();
//  RTC.begin();
    RTC.begin(DateTime(F(__DATE__), F(__TIME__)));

/*  if (! RTC.isrunning()) {
    Serial.println("RTC is NOT running!");
    // following line sets the RTC to the date & time this sketch was compiled
  }*/
  //UHR STELLEN
  //RTC.adjust(DateTime(F(__DATE__), F(__TIME__)));

  /* PINBELEGUNG */
  // HEBELSCHALTER
 /* pinMode(2, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);
  pinMode(4, INPUT_PULLUP);

  //  TASTER
  pinMode(6, INPUT_PULLUP);
  pinMode(17, INPUT_PULLUP);
  pinMode(21, INPUT_PULLUP);
  pinMode(22, INPUT_PULLUP);
  //pinMode(23, INPUT_PULLUP);

  //LEDS
  pinMode(5, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);

  //POTIS
  pinMode(14, INPUT);
  pinMode(15, INPUT);
  pinMode(16, INPUT);

  //VU-METER
  pinMode(23, OUTPUT);
  //BUILT-IN LED
  pinMode(13, OUTPUT);*/
}

void loop() {
  DateTime now = RTC.now();
  floppy.main(now.unixtime(), now.second(), now.minute(), now.hour(), now.day(), now.month(), now.year(), modeOne, modeTwo, modeThree, valueOne, valueTwo, valueThree, statusOne, statusTwo, statusThree, statusFour);
  printer.main(now.unixtime(), now.second(), now.minute(), now.hour(), now.day(), now.month(), now.year(), modeOne, modeTwo, modeThree, valueOne, valueTwo, valueThree, statusOne, statusTwo, statusThree, statusFour);
  tape.main(now.unixtime(), now.second(), now.minute(), now.hour(), now.day(), now.month(), now.year(), modeOne, modeTwo, modeThree, valueOne, valueTwo, valueThree, statusOne, statusTwo, statusThree, statusFour);

  Serial.println(now.second());

  //analogWrite(20, map(valueThree, 0, 1023, 50, 0));

  /* if(digitalRead(2) == HIGH){
     digitalWrite(12, HIGH);
     Serial.println("DGJFSAFMFADJ");
    } else {
     digitalWrite(12, LOW);
    }*/

  Serial.println(now.year());
}

/* void buttons() {
  digitalWrite(13, HIGH);

  if (digitalRead(4) == HIGH) {
    modeThree = 1;
    Serial.println("MODE 5 ACTIVATED.");
  } else {
    modeThree = 2;
    Serial.println("MODE 6 ACTIVATED.");
  }

  if (digitalRead(3) == HIGH) {
    modeTwo = 1;
    Serial.println("MODE 3 ACTIVATED.");
  } else {
    modeTwo = 2;
    Serial.println("MODE 4 ACTIVATED.");
  }

  if (digitalRead(2) == HIGH) {
    modeOne = 1;
    Serial.println("MODE 1 ACTIVATED.");
    Serial.println("1");
  } else {
    modeOne = 2;
    Serial.println("MODE 2 ACTIVATED.");
  }

  valueOne = analogRead(14);
  valueTwo = analogRead(15);
  valueThree = analogRead(16);

  if (digitalRead(17) == HIGH) {
    statusOne = 0;
  } else {
    statusOne = 1;
  }

  if (digitalRead(21) == HIGH) {
    statusTwo = 0;
  } else {
    statusTwo = 1;
  }

  if (digitalRead(22) == HIGH) {
    statusThree = 0;
  } else {
    statusThree = 1;
  }

  if (digitalRead(23) == HIGH) {
    statusFour = 0;
  } else {
    statusFour = 1;
  }
} */
