#include <AccelStepper.h>
#include <Encoder.h>


#define numSteppers 3

#define pinStep1 14
#define pinDir1 15
#define pinEndSwith1 53
#define RotaryCLK1 33 //CLK pin on the rotary encoder
#define RotaryDT1 25  //DT pin on the rotary encoder


#define pinStep2 16
#define pinDir2 17
#define pinEndSwith2 52
#define RotaryCLK1 24 //CLK pin on the rotary encoder
#define RotaryDT1 29  //DT pin on the rotary encoder

#define pinStep3 18
#define pinDir3 19
#define pinEndSwith3 51
#define RotaryCLK1 32 //CLK pin on the rotary encoder
#define RotaryDT1 45  //DT pin on the rotary encoder



// Variables to store current, previous and move position
int val[numSteppers] = {0, 0, 0};
int previous[numSteppers] = {-420, -420, -420};
long newval[numSteppers] = {0, 0, 0};
int endswitch_pins[numSteppers] = {pinEndSwith1, pinEndSwith2,pinEndSwith3};


AccelStepper stepper[numSteppers] = {
  AccelStepper(AccelStepper::FULL2WIRE, pinStep1, pinDir1),
  AccelStepper(AccelStepper::FULL2WIRE, pinStep2, pinDir2),
  AccelStepper(AccelStepper::FULL2WIRE, pinStep3, pinDir3)
};

Encoder encoder[numEncoder] = {
  Encoder(RotaryCLK1, RotaryDT1),
  Encoder(RotaryCLK2, RotaryDT2),
  Encoder(RotaryCLK3, RotaryDT3)
};


void setup() {

  Serial.begin(115200);

  
  stepper[0].setMaxSpeed(1000); //SPEED = Steps / second
  stepper[0].setAcceleration(500); //ACCELERATION = Steps /(second)^2

}

void loop(){

  newval[0] = Encoder[0].read();

  if (newval[0] != previous[0] ) {
    Serial.print("Position Encoder = ");
    Serial.println(newLeft);

    previous[0] = newval[0];
  }


  runTheMotor();

  // if a character is sent from the serial monitor,
  // reset both back to zero.
  if (Serial.available()) {
    Serial.read();
    Serial.println("Reset both knobs to zero");
    knobLeft.write(0);
    knobRight.write(0);
  }

}

void runTheMotor(AccelStepper stepper, int newval) //function for the motor
{    
    stepper.moveTo(newval*coef); //-1 is to match the rotation of the encoder with the rotation of the stepper
    while(stepper.distanceToGo() != 0)
    {
      stepper.runToNewPosition(newval*coef);
    }
    
}

void homing(AccelStepper stepper, int pin_end_switch){

  stepper.moveTo(1000);

  while(digitalRead(pin_end_switch[1]) == HIGH){
    stepper.runSpeed();
  }

  stepper.stop();
  stepper.setCurrentPosition(0);
  Serial.println("HIT NEW POSITION");

}


void setupControl(AccelStepper stepper, int pin_potard, int previous, int val, long newval, long mapMaxValue, int endswitch_pin){

  val=analogRead(pin_potard);

  stepper.runToPosition();

  Serial.println(stepper.currentPosition());

  if (digitalRead(endswitch_pin) == LOW) {
    stepper.setCurrentPosition(0);
    Serial.println("FUCK I JUST BUMPED INTO MYSELF");
  }
}

