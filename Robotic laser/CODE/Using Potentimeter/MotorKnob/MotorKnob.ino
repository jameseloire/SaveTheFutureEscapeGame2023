

#include <Stepper.h>

// change this to the number of steps on your motor
#define STEPS 200
#define K 5

// create an instance of the stepper class, specifying
// the number of steps of the motor and the pins it's
// attached to
Stepper stepper(STEPS,14, 15);
Stepper stepper2(STEPS,16, 17);

// the previous reading from the analog input
int previous = 0;
int previous2 = 0;
void setup() {
  // set the speed of the motor to 30 RPMs
  stepper.setSpeed(360);
  stepper2.setSpeed(360);
}

void loop() {
  // get the sensor value
  int val = analogRead(0)*K;
  long val2 = map(analogRead(1),0,1023,-100,-100);
  // move a number of steps equal to the change in the
  // sensor reading
  stepper.step(val - previous);
  stepper2.step(val2 - previous2);
  // remember the previous value of the sensor
  previous = val;
  previous2 = val2;
  
}