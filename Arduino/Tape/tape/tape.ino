/*************************************************


==== 1970 ====

TAPE RECEIVER: TAPE.INO
KENO WESTHOFF
HOCHSCHULE FÜR KÜNSTE BREMEN
2016


*************************************************/


// MOTOR PINS AND LEVELS
byte PWM_out_level;
const int motor1_A = 11;
const int motor1_B = 10;
const int PWM_out_pin = 9;

// LED PIN
const int LED = 13;

byte message;

void setup() {
  pinMode(motor1_A, OUTPUT);
  pinMode(motor1_B, OUTPUT);
  pinMode(PWM_out_pin, OUTPUT);
  Serial.begin(9600);

  digitalWrite(motor1_A, LOW);
  digitalWrite(motor1_B, HIGH);

  delay(20);
}

void loop() {
  /*if (Serial.available() > 0) {
    message = Serial.read();
    digitalWrite(13, HIGH);
  }*/

  PWM_out_level = 120;

  //PWM_out_level = map(message, 0, 128, 0, 128);
  //PWM_out_level = message;
  Serial.println(message);

  analogWrite(PWM_out_pin, PWM_out_level);
  //delay(500);
  Serial.println(PWM_out_level);
}
