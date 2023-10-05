


#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
Adafruit_PWMServoDriver alpha = Adafruit_PWMServoDriver(0x40);
Adafruit_PWMServoDriver beta = Adafruit_PWMServoDriver(0x41);


#define SERVOMIN 150   // This is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX 320   // This is the 'maximum' pulse length count (out of 4096)
#define USMIN 600      // This is the rounded 'minimum' microsecond length based on the minimum pulse of 150
#define USMAX 2400     // This is the rounded 'maximum' microsecond length based on the maximum pulse of 600
#define SERVO_FREQ 50  // Analog servos run at ~50 Hz updates


// Pin of the switch button connected to the nixie tube Alpla stand for the first box ( the one with the arduino)
#define Alfa_nixie1 14
#define Alfa_nixie2 15
#define Alfa_nixie3 16
#define Alfa_nixie4 17
#define Alfa_nixie5 18
#define Alfa_nixie6 19
#define Alfa_nixie7 13
#define Alfa_nixie8 12

int pinNixieAlpha1[4] = { Alfa_nixie1, Alfa_nixie2, Alfa_nixie3, Alfa_nixie4 };
int pinNixieAlpha2[4] = { Alfa_nixie5, Alfa_nixie6, Alfa_nixie7, Alfa_nixie8 };

// Pin of the switch button connected to the nixie tube Beta stand for the second box ( the one without the arduino)
#define Beta_nixie1 50
#define Beta_nixie2 46
#define Beta_nixie3 51
#define Beta_nixie4 48
#define Beta_nixie5 34
#define Beta_nixie6 38
#define Beta_nixie7 42
#define Beta_nixie8 24


int pinNixieBeta1[4] = { Beta_nixie1, Beta_nixie2, Beta_nixie3, Beta_nixie4 };
int pinNixieBeta2[4] = { Beta_nixie5, Beta_nixie6, Beta_nixie7, Beta_nixie8 };

//Pin of the digit 1 Box Alpha

#define Digit1_A 23
#define Digit1_B 27
#define Digit1_C 31
#define Digit1_D 33
#define Digit1_E 35
#define Digit1_F 29
#define Digit1_G 25


//Pin of the digit 2 Box Alpha

#define Digit2_A 39
#define Digit2_B 49
#define Digit2_C 37
#define Digit2_D 43
#define Digit2_E 45
#define Digit2_F 41
#define Digit2_G 47

//Pin of the digit 3 Box Beta

#define Digit3_A 40
#define Digit3_B 3
#define Digit3_C 2
#define Digit3_D 53
#define Digit3_E 28
#define Digit3_F 30
#define Digit3_G 32

//Pin of the digit 4 Box Beta
#define Digit4_A 22
#define Digit4_B 52
#define Digit4_C 44
#define Digit4_D 4
#define Digit4_E 5
#define Digit4_F 26
#define Digit4_G 36


int pinServoAlpha[14] = {
  Digit1_A, Digit1_B, Digit1_C, Digit1_D, Digit1_E, Digit1_F, Digit1_G,
  Digit2_A, Digit2_B, Digit2_C, Digit2_D, Digit2_E, Digit2_F, Digit2_G
};

int StateServoAlpha[14] = {};
int StateServoBeta[14] = {};



int pinServoBeta[14] = {
  Digit3_A, Digit3_B, Digit3_C, Digit3_D, Digit3_E, Digit3_F, Digit3_G,
  Digit4_A, Digit4_B, Digit4_C, Digit4_D, Digit4_E, Digit4_F, Digit4_G
};


#define SECRET_DATE 1905


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600 );
  alpha.begin();
  alpha.setOscillatorFrequency(27000000);
  alpha.setPWMFreq(SERVO_FREQ);  // Analog servos run at ~50 Hz updates
  delay(100);


  beta.begin();
  beta.setOscillatorFrequency(27000000);
  beta.setPWMFreq(SERVO_FREQ);  // Analog servos run at ~50 Hz updates
  delay(100);

  for (int i = 0; i < 14; i++) {
    StateServoAlpha[14] = 0;
    StateServoBeta[14] = 0;
  }



  for (int i = 0; i < 54; i++) {
    pinMode(i, INPUT_PULLUP);  // set every one as a pull up so we will detect when the pin will be connected to the gnd
  }
}

void loop() { 

  Serial.print("Save me");
  // put your main code here, to run repeatedly:
 
  if (readNixieTubes() == SECRET_DATE) {
    Serial.println("WINNN!!!!");
  }
 
  readNixieTubes();
  displayServo();


}


long readNixieTubes() {

  long value = 0;
  int curentVal = 0;


  // for the FIRST Nixie
  for (byte count = 0; count < 4; count++) {
    bitWrite(curentVal, count, digitalRead(pinNixieAlpha1[count]));
  }                           // end of for count
  value += 1000 * curentVal;  // BASE 10
  curentVal = 0;


  // for the SECOND Nixie
  for (byte count = 0; count < 4; count++) {
    bitWrite(curentVal, count, digitalRead(pinNixieAlpha2[count]));
  }  // end of for count
  value += 100 * curentVal;
  curentVal = 0;


  // for the THIRD Nixie
  for (byte count = 0; count < 4; count++) {
    bitWrite(curentVal, count, digitalRead(pinNixieBeta1[count]));
  }  // end of for count
  value += 10 * curentVal;
  curentVal = 0;



  // for the FOURTH Nixie
  for (byte count = 0; count < 4; count++) {
    bitWrite(curentVal, count, digitalRead(pinNixieBeta2[count]));
  }  // end of for count
  value += curentVal;
  curentVal = 0;

  Serial.println(value);
  return value;
}

void displayServo() {

  for (int servoNumber = 0; servoNumber < 14; servoNumber++) {

    if (digitalRead(pinServoAlpha[servoNumber]) == LOW) {

      if (StateServoAlpha[servoNumber] == 1) {

        turnServo(servoNumber, true, true);
        Serial.print(" ALPHA Nb : ");
        Serial.print(servoNumber);
        Serial.println("  State OPEN");
        StateServoAlpha[servoNumber] = 0;
      }


    } else {

      if (StateServoAlpha[servoNumber] == 0) {

        turnServo(servoNumber, true, false);
        Serial.print(" ALPHA  Nb : ");
        Serial.print(servoNumber);
        Serial.println("  State CLOSE");
        StateServoAlpha[servoNumber] = 1;
      }
    }


    if (digitalRead(pinServoBeta[servoNumber]) == LOW) {

      if (StateServoBeta[servoNumber] == 1) {

        turnServo(servoNumber, false, true);
        Serial.print(" BETA  Nb : ");
        Serial.print(servoNumber);
        Serial.println("  State OPEN");
        StateServoBeta[servoNumber] = 0;
      }

    } else {

      if (StateServoBeta[servoNumber] == 0) {

        turnServo(servoNumber, false, false);
        Serial.print(" BETA  Nb : ");
        Serial.print(servoNumber);
        Serial.println("  State CLOSE");
        StateServoBeta[servoNumber] = 1;
      }
    }
  }
}



void turnServo(uint8_t servonum, bool isAlpha, bool open) {
  if (isAlpha) {
    if (open) {

      for (uint16_t pulselen = SERVOMIN; pulselen < SERVOMAX; pulselen++) {
        alpha.setPWM(servonum, 0, pulselen);
      }
    } else {
      for (uint16_t pulselen = SERVOMAX; pulselen > SERVOMIN; pulselen--) {
        alpha.setPWM(servonum, 0, pulselen);
      }
    }

  }


  else {
    if (open) {

      for (uint16_t pulselen = SERVOMIN; pulselen < SERVOMAX; pulselen++) {
        beta.setPWM(servonum, 0, pulselen);
      }

    } else {
      for (uint16_t pulselen = SERVOMAX; pulselen > SERVOMIN; pulselen--) {
        beta.setPWM(servonum, 0, pulselen);
      }
    }
  }
}



void readPins() {
  for (int i = 0; i < 54; i++) {
    Serial.print(i);
    Serial.print(" state ");
    Serial.println(digitalRead(i));  // set every one as a pull up so we will detect when the pin will be connected to the gnd
  }
}


void homing(){

  for(int servonum =0 ;servonum<14;servonum++){
    
    turnServo(servonum, true, true);
    turnServo(servonum, false, true);
  }
}
