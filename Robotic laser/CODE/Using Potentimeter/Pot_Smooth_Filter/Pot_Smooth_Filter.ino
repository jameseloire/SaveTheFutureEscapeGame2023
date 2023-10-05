// Define the number of samples to keep track of. The higher the number, the
// more the readings will be smoothed, but the slower the output will respond to
// the input. Using a constant rather than a normal variable lets us use this
// value to determine the size of the readings array.
const int numReadings = 10;
const int numPins = 5; // Number of analog input pins being used
const int threshold = 2; // Threshold for detecting changes in potentiometer readings
const int coef = 1;

int readings[numPins][numReadings];  // the readings from the analog input
int readIndex[numPins];          // the index of the current reading
int total[numPins];              // the running total
int average[numPins];            // the average
int direction[numPins];           // the direction array

int inputPins[numPins] = {A0, A1, A2, A3, A4}; // Array of analog input pins being used

void smoothAnalogInputs() {
  // Loop through all the analog input pins being used
  for (int i = 0; i < numPins; i++) {
    int inputPin = inputPins[i]; // Get the current input pin

    // subtract the last reading:
    total[i] = total[i] - readings[i][readIndex[i]];

    // read from the sensor:
    readings[i][readIndex[i]] = analogRead(inputPin) * coef;

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


      } else if (new_avg < average[i]) {
        Serial.println("Direction: Counterclockwise");
        direction[i]=-1;
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
      average[i] = new_avg;
    }
  }

  delay(1);  // delay in between reads for stability
}

void setup() {
  // initialize serial communication with computer:
  Serial.begin(9600);
 
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
