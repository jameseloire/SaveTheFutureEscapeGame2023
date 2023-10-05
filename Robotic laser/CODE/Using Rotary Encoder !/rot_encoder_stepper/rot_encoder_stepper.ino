
int stepPin =16;
int dirPin = 17;
int coef= 50;


#include <AccelStepper.h>
AccelStepper small_stepper(1, 16, 17);// pulses Digital 9 (CLK); Direction Digital 8 (CCW)



volatile boolean TurnDetected;  // need volatile for Interrupts
volatile boolean rotationdirection;  // CW or CCW rotation

const int PinCLK=2;   // Generating interrupts using CLK signal
const int PinDT=4;    // Reading DT signal
const int PinSW=3;    // Reading Push Button switch

int RotaryPosition=0;    // To store Stepper Motor Position

int PrevPosition;     // Previous Rotary position Value to check accuracy
int StepsToTake;      // How much to move Stepper

// Setup of proper sequencing for Motor Driver Pins
// In1, In2, In3, In4 in the sequence 1-3-2-4
// Interrupt routine runs if CLK goes from HIGH to LOW
void isr ()  {
  delay(4);  // delay for Debouncing
  if (digitalRead(PinCLK))
    rotationdirection= digitalRead(PinDT);
  else
    rotationdirection= !digitalRead(PinDT);
  TurnDetected = true;
}

void setup ()  {
  
pinMode(PinCLK,INPUT);
pinMode(PinDT,INPUT);  
pinMode(PinSW,INPUT_PULLUP);
digitalWrite(PinSW, HIGH); // Pull-Up resistor for switch
attachInterrupt (0,isr,FALLING); // interrupt 0 always connected to pin 2 on Arduino UNO
Serial.begin(115200);
}

void loop ()  {
  small_stepper.setSpeed(600); //Max seems to be 700
  if (!(digitalRead(PinSW))) {   // check if button is pressed
    if (RotaryPosition == 0) {  // check if button was already pressed
    } else {
        small_stepper.step(-(RotaryPosition*coef));
        RotaryPosition=0; // Reset position to ZERO
      }
    }

  // Runs if rotation was detected
  if (TurnDetected)  {
    PrevPosition = RotaryPosition; // Save previous position in variable
    if (rotationdirection) {
      Serial.println("CLKWISE");
      RotaryPosition=RotaryPosition-1;} // decrase Position by 1
    else {
      Serial.println("----------------------ANTI CLKWISE");
      RotaryPosition=RotaryPosition+1;} // increase Position by 1

    TurnDetected = false;  // do NOT repeat IF loop until new rotation detected

    // Which direction to move Stepper motor
    if ((PrevPosition + 1) == RotaryPosition) { // Move motor CW
      
      Serial.println("turn ANTI CLK");
      
    
    }

    if ((RotaryPosition + 1) == PrevPosition) { // Move motor CCW
      
      Serial.println("turn CLK");
      
      
    }
  }
}