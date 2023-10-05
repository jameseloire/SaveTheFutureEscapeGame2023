// moving avg on knobs to smooth the movement and stop final position
const int numReadings = 10;
const int numPins = 1; // Number of analog input pins being used
const int threshold = 2; // Threshold for detecting changes in potentiometer readings
#define DELAY 500
int stepPin =16;
int dirPin = 17;

int readings[numPins][numReadings];  // the readings from the analog input
int readIndex[numPins];          // the index of the current reading
int total[numPins];              // the running total
int average[numPins];            // the average
int direction[numPins];           // the direction array

int inputPins[numPins] = {A0}; // Array of analog input pins being used

void smoothAnalogInputs() {
  // Loop through all the analog input pins being used
  for (int i = 0; i < numPins; i++) {
    int inputPin = inputPins[i]; // Get the current input pin

    // subtract the last reading:
    total[i] = total[i] - readings[i][readIndex[i]];

    // read from the sensor:
    readings[i][readIndex[i]] = analogRead(inputPin);

    // add the reading to the total:
    total[i] = total[i] + readings[i][readIndex[i]];

    // advance to the next position in the array:
    readIndex[i] = readIndex[i] + 1;

    // if we're at the end of the array...
    if (readIndex[i] >= numReadings) {
      // ...wrap around to the beginning:
      readIndex[i] = 0;
    }

    // calculate the new average:
    int new_avg = abs(total[i] / numReadings);

    // compare the variation between the new average and previous average with threshold:
    if (abs(new_avg - average[i]) > threshold) {
      // If the variation is greater than threshold, trigger an event.
      // In this example, we print the new average to the serial monitor.
     

      // Determine the direction of rotation
      if (new_avg > average[i]) {
        Serial.println("Direction: Clockwise");
        direction[i]=1;

        digitalWrite(dirPin,HIGH); 

        for(int x = 0; x < new_avg; x++) {

          digitalWrite(stepPin,HIGH); 
          delayMicroseconds(DELAY);    // by changing this time delay between the steps we can change the rotation speed
          digitalWrite(stepPin,LOW); 
          delayMicroseconds(DELAY); 
    
          }


      } else if (new_avg < average[i]) {
        Serial.println("Direction: Counterclockwise");
        direction[i]=-1;


          digitalWrite(dirPin,LOW); 

        for(int x = 0; x < new_avg; x++) {

          digitalWrite(stepPin,HIGH); 
          delayMicroseconds(DELAY);    // by changing this time delay between the steps we can change the rotation speed
          digitalWrite(stepPin,LOW); 
          delayMicroseconds(DELAY); 
    
          }


      } else {
        Serial.println("Direction: No change");
        direction[i]=0;
      }

      
      Serial.print("Smoothed Value for A");
      Serial.print(i);
      Serial.print("  ------  Direction of rot : ");
      Serial.print(direction[i]);      
      Serial.print("   -------- Value :  ");
      Serial.println(new_avg);


      // Update the average with the new value
      average[i] = (new_avg *0.05)+(average[i]*0.95) ;
    
    }
  }

  delay(1);  // delay in between reads for stability
}

void setup() {
  // initialize serial communication with computer:
  Serial.begin(9600);
  pinMode(stepPin,OUTPUT); 
  pinMode(dirPin,OUTPUT);
 
  // initialize all the readings and running totals to 0:
  for (int i = 0; i < numPins; i++) {
    for (int j = 0; j < numReadings; j++) {
      readings[i][j] = 0;
    }
    readIndex[i] = 0;
    total[i] = 0;
  }
}

void loop() {
  smoothAnalogInputs();
}
