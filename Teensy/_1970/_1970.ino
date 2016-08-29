/*************************************************


  ==================================================
                      1970
  ==================================================


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

volatile int modeOne;
volatile int modeTwo;
volatile int modeThree;

int valueOne;
int valueTwo;
int valueThree;

volatile int statusOne = 0;
volatile int statusTwo = 0;
volatile int statusThree = 0;
volatile int statusFour = 0;

// PINS
// HEBELSCHALTER
const int leverOne = 2;
const int leverTwo = 3;
const int leverThree = 4;

// TASTER
const int switchOne = 17;
const int switchTwo = 21;
const int switchThree = 22;
const int switchFour = 23;

// LEDS
const int ledOne = 5;
const int ledTwo = 11;
const int ledThree = 12;

// POTIS
const int potOne = 14;
const int potTwo = 15;
const int potThree = 16;

// VU-METER
const int vuPin = 20;

// BUILT-IN LED
const int bLED = 13;

// BOUNCE
volatile unsigned long oldTime = 0, bounceTime = 1000;

/* SETUP */
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
  pinMode(leverOne, INPUT_PULLUP);
  pinMode(leverTwo, INPUT_PULLUP);
  pinMode(leverThree, INPUT_PULLUP);

  //  TASTER
  pinMode(switchOne, INPUT_PULLUP);
  pinMode(switchTwo, INPUT_PULLUP);
  pinMode(switchThree, INPUT_PULLUP);
  pinMode(switchFour, INPUT_PULLUP);

  //LEDS
  pinMode(ledOne, OUTPUT);
  pinMode(ledTwo, OUTPUT);
  pinMode(ledThree, OUTPUT);

  //POTIS
  pinMode(potOne, INPUT);
  pinMode(potTwo, INPUT);
  pinMode(potThree, INPUT);

  //VU-METER
  pinMode(vuPin, OUTPUT);

  //BUILT-IN LED
  pinMode(bLED, OUTPUT);

  // INTERRUPTS EINRICHTEN
  // HEBELSCHALTER

  //FALLING
  attachInterrupt(digitalPinToInterrupt (leverOne), triggerLeverOne, CHANGE);
  attachInterrupt(digitalPinToInterrupt (leverTwo), triggerLeverTwo, CHANGE);
  attachInterrupt(digitalPinToInterrupt (leverThree), triggerLeverThree, CHANGE);

  // TASTER
  attachInterrupt(digitalPinToInterrupt (switchOne), triggerSwitchOne, FALLING);
  attachInterrupt(digitalPinToInterrupt (switchTwo), triggerSwitchTwo, FALLING);
  attachInterrupt(digitalPinToInterrupt (switchThree), triggerSwitchThree, FALLING);
  attachInterrupt(digitalPinToInterrupt (switchFour), triggerSwitchFour, FALLING);

  delay(10);

  // INITIALISE LEVER SWITCHES
  if (digitalRead(leverOne) == LOW)
  {
    modeOne = 2;
  }
  else if (digitalRead(leverOne) == HIGH)
  {
    modeOne = 1;
  }

  if (digitalRead(leverTwo) == LOW)
  {
    modeTwo = 2;
  }
  else if (digitalRead(leverTwo) == HIGH)
  {
    modeTwo = 1;
  }

  if (digitalRead(leverThree) == LOW)
  {
    modeThree = 2;
  }
  else if (digitalRead(leverThree) == HIGH)
  {
    modeThree = 1;
  }
}

void loop() {
  DateTime now = RTC.now();
  floppy.main(now.unixtime(), now.second(), now.minute(), now.hour(), now.day(), now.month(), now.year(), modeOne, modeTwo, modeThree, valueOne, valueTwo, valueThree, statusOne, statusTwo, statusThree, statusFour);
  printer.main(now.unixtime(), now.second(), now.minute(), now.hour(), now.day(), now.month(), now.year(), modeOne, modeTwo, modeThree, valueOne, valueTwo, valueThree, statusOne, statusTwo, statusThree, statusFour);
  tape.main(now.unixtime(), now.second(), now.minute(), now.hour(), now.day(), now.month(), now.year(), modeOne, modeTwo, modeThree, valueOne, valueTwo, valueThree, statusOne, statusTwo, statusThree, statusFour);
  Serial.println(now.second());

  analogWrite(vuPin, map(sin(0.2*now.second()), -1, 1, 0, 25));

  output();

  // POTIS
  valueOne = analogRead(potOne);
  valueTwo = analogRead(potTwo);
  valueThree = analogRead(potThree);
  Serial.println(valueOne);
  Serial.println(valueTwo);
  Serial.println(valueThree);

  buttons();
}

void buttons() {
  digitalWrite(bLED, HIGH);
}

// INTERRUPTS
// HEBELSCHALTER
void triggerLeverThree()
{
  Serial.println("THREE FALLING.");
  if (modeThree == 2)
  {
    modeThree = 1;
  }
  else
  {
    modeThree = 2;
  }
}

void triggerLeverTwo()
{
  Serial.println("TWO CHANGING.");
  if (modeTwo == 2)
  {
    modeTwo = 1;
  }
  else
  {
    modeTwo = 2;
  }
}

void triggerLeverOne()
{
  Serial.println("ONE CHANGING.");
  if (modeOne == 2)
  {
    modeOne = 1;
  }
  else
  {
    modeOne = 2;
  }
}

// SWITCHES
void triggerSwitchOne()
{
  if ((millis() - oldTime) > bounceTime)
  {
    Serial.println("ONE CHANGING.");
    if (statusOne == 1)
    {
      statusOne = 0;
      digitalWrite(5, LOW);
    }
    else
    {
      statusOne = 1;
      digitalWrite(5, HIGH);
    }
  }
  else {}
  sei();
  interrupts();
  oldTime = millis();
}

void triggerSwitchTwo()
{
  Serial.println("TWO CHANGING.");
  if (statusTwo == 1)
  {
    statusTwo = 0;
    digitalWrite(11, LOW);
  }
  else
  {
    statusTwo = 1;
    digitalWrite(11, HIGH);
  }
}

void triggerSwitchThree()
{
  Serial.println("THREE CHANGING.");
  if (statusThree == 1)
  {
    statusThree = 0;
    digitalWrite(12, LOW);
  }
  else
  {
    statusThree = 1;
    digitalWrite(12, HIGH);
  }
}


void triggerSwitchFour()
{
  Serial.println("FOUR CHANGING.");
  if (statusFour == 1)
  {
    statusFour = 0;
    digitalWrite(5, LOW);
    digitalWrite(12, LOW);
  }
  else
  {
    statusFour = 1;
    digitalWrite(5, HIGH);
    digitalWrite(12, HIGH);
  }
}


void output()
{
  // AUSGABEKONTROLLE
  Serial.println("============");
  Serial.println("MODES");
  Serial.println("––––––––––––");
  Serial.println(modeOne);
  Serial.println(modeTwo);
  Serial.println(modeThree);
  Serial.println("––––––––––––");
  Serial.println("MODES END");
  Serial.println("============");
  Serial.println("STATUS");
  Serial.println("––––––––––––");
  Serial.println(statusOne);
  Serial.println(statusTwo);
  Serial.println(statusThree);
  Serial.println(statusFour);
  Serial.println("––––––––––––");
  Serial.println("STATUS END");
  Serial.println("============");
  Serial.println("MESSAGES");
  Serial.println(floppy.message);
  Serial.println(tape.message);
  Serial.println(printer.message);
  Serial.println("MESSAGES END");
  Serial.println("============");
}

