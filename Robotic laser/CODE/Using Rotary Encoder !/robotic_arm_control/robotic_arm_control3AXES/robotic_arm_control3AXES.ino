#include <AccelStepper.h>
#include <Encoder.h>
#include <LiquidCrystal_I2C.h>


#define numSteppers 3
#define ENABLEMOTOR 23


#define pinStep1 19
#define pinDir1 18
#define pinEndSwitch1 13
#define RotaryCLK1 13 //CLK pin on the rotary encoder
#define RotaryDT1   13  //DT pin on the rotary encoder

#define pinStep2 5
#define pinDir2 17
#define pinEndSwitch2 13
#define RotaryCLK2 13 //CLK pin on the rotary encoder
#define RotaryDT2 13 //DT pin on the rotary encoder

#define pinStep3 16
#define pinDir3 4
#define pinEndSwitch3 13
#define RotaryCLK3 13 //CLK pin on the rotary encoder
#define RotaryDT3 13  //DT pin on the rotary encoder

int endSwitchPins[numSteppers] = {pinEndSwitch1, pinEndSwitch2, pinEndSwitch3};

LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display

AccelStepper stepper[numSteppers] = {
  AccelStepper(AccelStepper::FULL2WIRE, pinStep1, pinDir1),
  AccelStepper(AccelStepper::FULL2WIRE, pinStep2, pinDir2),
  AccelStepper(AccelStepper::FULL2WIRE, pinStep3, pinDir3)
};

Encoder encoder[numSteppers] = {
  Encoder(RotaryCLK1, RotaryDT1),
  Encoder(RotaryCLK2, RotaryDT2),
  Encoder(RotaryCLK3, RotaryDT3)
};

int val[numSteppers] = {0, 0, 0};
int previous[numSteppers] = {-420, -420, -420};
long newval[numSteppers] = {0, 0, 0};



long positionLeft  = -999;
long positionRight = -999;
long positionMid = -999;

Encoder knobLeft(32, 33);
Encoder knobMid(25, 26);
Encoder knobRight(27, 14);


void setup() {
  Serial.begin(9600);
  lcd.init();
  lcd.setBacklight(100);
  lcd.setCursor(0,0);
  lcd.print(" Save the Futur !");    

  for (int i = 0; i < numSteppers; i++) {
    stepper[i].setMaxSpeed(10000); //SPEED = Steps / second
    stepper[i].setAcceleration(5000); //ACCELERATION = Steps /(second)^2
    pinMode(endSwitchPins[i], INPUT_PULLUP);
  }
  digitalWrite(ENABLEMOTOR, HIGH);
  delay(3000);
}

void loop() {

  long newLeft, newRight, newMid;
  
  newLeft = knobLeft.read();
  newRight = knobRight.read();
  newMid = knobMid.read();
  
  if (newLeft != positionLeft || newRight != positionRight || newMid != positionMid) {

    Serial.print("Left = ");
    Serial.println(newLeft);
    Serial.print(", Mid = ");
    Serial.println(newMid);
    Serial.print(", Right = ");
    Serial.println(newRight);
    Serial.println();

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("X: ");
    lcd.print(String(newLeft));
    lcd.print("  Y: "); 
    lcd.print(String(newMid));
    lcd.setCursor(0, 1);
    lcd.print("Z: ");
    lcd.print(String(newRight));


    positionLeft = newLeft;
    positionRight = newRight;
    positionMid = newMid;
  }
    runTheMotor(stepper[0], positionLeft);
    runTheMotor(stepper[1], positionMid);
    runTheMotor(stepper[2], positionRight);

    if ((stepper[0].distanceToGo() == 0) && (stepper[1].distanceToGo() == 0) && (stepper[2].distanceToGo() == 0)){
      digitalWrite(ENABLEMOTOR, HIGH);
    }
    else {
    digitalWrite(ENABLEMOTOR, LOW);
    }
      
 

  // if a character is sent from the serial monitor,
  // reset both back to zero.
  if (Serial.available()) {
    Serial.read();
    Serial.println("Reset all encoders to zero");
    for (int i = 0; i < numSteppers; i++) {
      encoder[i].write(0);
      stepper[i].moveTo(0);
    }
    delay(1000);
  }
}

void runTheMotor(AccelStepper& stepper, int newval) {
  int coef = 100; // Define the coefficient to match the rotation of the encoder with the rotation of the stepper
  stepper.moveTo(newval * coef);
  stepper.run();
}



void homing(AccelStepper& stepper, int endSwitchPin) {

  const int homingSpeed = 200; // Set homing speed (steps per second)
  stepper.setSpeed(homingSpeed); // Set the speed for homing

  // Move the stepper motor towards the end switch until it is triggered
  while (digitalRead(endSwitchPin) == HIGH) {
    stepper.runSpeed();
  }
  
  // Stop the stepper motor when the end switch is triggered
  stepper.stop();

  // Set the current position as the home position
  stepper.setCurrentPosition(0);

  // Print a message indicating the homing is complete
  Serial.println("Homing completed");

}