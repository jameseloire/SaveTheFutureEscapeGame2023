#include <AccelStepper.h>

#define pinPotard A0
#define pinEndSwith 3
#define pinStep 5
#define pinDir 2


// Variables to store current, previous and move position
int val = 0;
int previous = 0;
int long newval = 0;   
int potard_error=50;
int long mapMaxValue=10000;


AccelStepper stepper1(AccelStepper::FULL2WIRE,pinStep ,pinDir);

void homing(AccelStepper stepper, int pin_end_switch){
  stepper.moveTo(10000);
  while(digitalRead(pin_end_switch) == HIGH){
    stepper.runSpeed();
  }
  stepper.stop();
  stepper.setCurrentPosition(0);
  Serial.println("HIT NEW POSITION");
  Serial.println(stepper.currentPosition());
}


void setupControl(AccelStepper stepper,int pin_potard, int potard_error, int previous, int val, int long newval, int mapMaxValue){

  val = analogRead(pin_potard);

  if((val > previous+potard_error) || (val < previous-potard_error)){
    newval = map(val,0,1023,0,mapMaxValue);
    stepper.moveTo(newval);
    previous = val;
    Serial.println(stepper.currentPosition());
  }
  stepper.run();
} 
void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);
  pinMode(pinEndSwith,INPUT_PULLUP);
  pinMode(pinPotard,INPUT);

  stepper1.setMaxSpeed(1000000);  // Set speed fast enough to follow pot rotation
  stepper1.setAcceleration(1000000); 
  
  homing(stepper1,pinEndSwith);
 
  
  Serial.println("setup"); 
}

void loop() {
  // put your main code here, to run repeatedly:


  val = analogRead(pinPotard);

  if((val > previous+potard_error) || (val < previous-potard_error)){
    newval = map(val,0,1023,0,mapMaxValue);
    stepper1.moveTo(newval);
    previous = val;
    Serial.println(stepper1.currentPosition());
  }
  stepper1.run();

}
