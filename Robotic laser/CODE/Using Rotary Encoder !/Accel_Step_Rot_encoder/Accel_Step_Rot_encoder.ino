//AccelStepper
#include <AccelStepper.h>
#define step 26
#define dir 27
AccelStepper stepper(1, step, dir);// pulses Digital 9 (CLK); Direction Digital 8 (CCW)

//16x2 LCD



//Defining pins
const int RotaryCLK = 33; //CLK pin on the rotary encoder
const int RotaryDT = 25; //DT pin on the rotary encoder

int coef= 30;

//Defining variables
int RotateCounter = 0;

//Statuses
int CLKNow;
int CLKPrevious;

int DTNow;
int DTPrevious;



void setup()
{

  Serial.begin(9600);
  
	//------------------------------------------------------
	
  //------------------------------------------------------

   pinMode(RotaryCLK, INPUT);
   pinMode(RotaryDT, INPUT);

   

  //Store states
  CLKPrevious = digitalRead(RotaryCLK);
  DTPrevious = digitalRead(RotaryDT);
    
  attachInterrupt(digitalPinToInterrupt(RotaryCLK), rotate, CHANGE);
 
  stepper.setMaxSpeed(10000); //SPEED = Steps / second
  stepper.setAcceleration(5000); //ACCELERATION = Steps /(second)^2

  
}


void loop()
{
  
  RunTheMotor();
  Serial.println(RotateCounter);
}

void rotate()
{
  CLKNow = digitalRead(RotaryCLK); //Read the state of the CLK pin

  // If last and current state of CLK are different, then a pulse occurred  
  if (CLKNow != CLKPrevious  && CLKNow == 1){

    // If the DT state is different than the CLK state then
    // the encoder is rotating CCW so increase
    if (digitalRead(RotaryDT) != CLKNow) {
      RotateCounter++;
      
    } else {
      // Encoder is rotating CW so decrease
      RotateCounter--;      
    }    
  }
  CLKPrevious = CLKNow;  // Store last CLK state
}



void RunTheMotor() //function for the motor
{    
    
    stepper.moveTo(RotateCounter*coef); //-1 is to match the rotation of the encoder with the rotation of the stepper
    while(stepper.distanceToGo() != 0)
    {
      stepper.runToNewPosition(RotateCounter*coef);
    }
    
}