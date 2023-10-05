#include <AccelStepper.h>

#define pinPotard A0
#define pinEndSwith 2
#define pinStep 3
#define pinDir 4

#define pinPotardShoulder A1
#define pinEndSwitchShoulder 5
#define pinStepShoulder 6
#define pinDirShoulder 7

#define pinPotardElbow A2 
#define pinEndSwitchElbow 8
#define pinStepElbow 9
#define pinDirElbow 10

#define pinPotardWrist A3
#define pinEndSwitchWrist 11
#define pinStepWrist 12
#define pinDirWrist 13

#define pinPotardHand A4
#define pinStepHand 14
#define pinDirHand 15

// Variables to store current, previous and move position
int val = 0;
int previous = 0;
int long newval = 0;   
int long  currentPosition=0;
int long acceleration=0;
//Shoulder vars
int val_shoulder = 0;
int previous_shoulder = 0;
int long newval_shoulder = 0;
int long currentPositionShoulder = 0;
int long accelerationShoulder = 0;
//ShoulElbowder vars
int val_elbow = 0;
int previous_elbow = 0;
int long newval_elbow = 0;
int long currentPositionElbow = 0;
int long accelerationElbow = 0;
//wrist vars
int val_wrist = 0;
int previous_wrist = 0;
int long newval_wrist = 0;
int long currentPositionWrist = 0;
int long accelerationWrist = 0;
//Hand vars
int val_hand = 0;
int previous_hand = 0;
int long newval_hand = 0;
int long currentPositionHand = 0;
int long accelerationHand = 0;

AccelStepper stepper1(AccelStepper::FULL2WIRE,pinStep ,pinDir);
AccelStepper stepperShoulder(AccelStepper::FULL2WIRE,pinStepShoulder, pinDirShoulder);
AccelStepper stepperElbow(AccelStepper::FULL2WIRE,pinStepElbow, pinDirElbow);
AccelStepper stepperWrist(AccelStepper::FULL2WIRE,pinStepWrist, pinDirWrist);
AccelStepper stepperHand(AccelStepper::FULL2WIRE,pinStepHand, pinDirHand);

void homing0() { // call when end switch hit -- object Steppercall in param
	
  while(digitalRead(pinEndSwith) == HIGH) {
    stepper1.runSpeed();
    Serial.println(stepper1.currentPosition());
  }
   stepper1.stop();
   stepper1.setCurrentPosition(0);// refresh new position
   Serial.println("HIT NEW POSITION ");
   Serial.println(stepper1.currentPosition());
}

void homing(AccelStepper stepper, int pin_end_switch){
  while(digitalRead(pin_end_switch) == HIGH){
    stepper.runSpeed();
    Serial.println(stepper.currentPosition());
  }
  stepper.stop();
  stepper.setCurrentPosition(0);
  Serial.println("HIT NEW POSITION");
  Serial.println(stepper.currentPosition());
}

void setupControl(AccelStepper stepper,int pin_potard, int potard_error, int p, int v, int long nv, int mapMaxValue){
  v = analogRead(pin_potard);
  
  Serial.println(stepper.currentPosition());

  if((v > p+potard_error) || (v < p-potard_error)){
    nv = map(v,0,1023,0,mapMaxValue);
    stepper.runToNewPosition(nv);
    p = v;
  }
} 

void setup()
{  
  Serial.begin(9600);
  pinMode(pinEndSwith,INPUT_PULLUP);
  pinMode(pinEndSwitchElbow,INPUT_PULLUP);
  pinMode(pinEndSwitchShoulder,INPUT_PULLUP);
  pinMode(pinEndSwitchWrist,INPUT_PULLUP);
  pinMode(pinPotard,INPUT);
  pinMode(pinPotardElbow,INPUT);
  pinMode(pinPotardHand,INPUT);
  pinMode(pinPotardShoulder,INPUT);
  pinMode(pinPotardWrist,INPUT);
  stepper1.setMaxSpeed(4800);  // Set speed fast enough to follow pot rotation
  stepper1.setSpeed(3000);
  stepper1.setAcceleration(1000); 
  stepperElbow.setMaxSpeed(4800);  // Set speed fast enough to follow pot rotation
  stepperElbow.setSpeed(3000);
  stepperElbow.setAcceleration(1000); 

  stepperShoulder.setMaxSpeed(4800);  // Set speed fast enough to follow pot rotation
  stepperShoulder.setSpeed(3000);
  stepperShoulder.setAcceleration(1000); 

  stepperWrist.setMaxSpeed(4800);  // Set speed fast enough to follow pot rotation
  stepperWrist.setSpeed(3000);
  stepperWrist.setAcceleration(1000); 
  stepperHand.setMaxSpeed(4800);  // Set speed fast enough to follow pot rotation
  stepperHand.setSpeed(3000);
  stepperHand.setAcceleration(1000); 
 // homing0();
  //homing(stepperWrist,pinEndSwitchWrist);
  homing(stepperShoulder,pinEndSwitchShoulder);
 // homing(stepperElbow,pinEndSwitchElbow);
  
  Serial.println("setup"); 
}

void loop()
{
  setupControl(stepper1,pinPotard,50,previous,val,newval,3000);
  setupControl(stepperShoulder,pinPotardShoulder,20,previous_shoulder,val_shoulder,newval_shoulder,1000);
  setupControl(stepperElbow,pinPotardElbow,50,previous_elbow,val_elbow,newval_elbow,1000);
  setupControl(stepperWrist,pinPotardWrist,50,previous_wrist,val_wrist,newval_wrist,1000);
  setupControl(stepperHand,pinPotardHand,50,previous_hand,val_hand,newval_hand,6400);
}

