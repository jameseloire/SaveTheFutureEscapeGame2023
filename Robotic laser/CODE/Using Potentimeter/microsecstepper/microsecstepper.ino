// defines pins
int stepPin =26;
int dirPin = 27;
int previous = 0;

#define DELAY 200
 
void setup() {
  // Sets the two pins as Outputs
  pinMode(stepPin,OUTPUT); 
  pinMode(dirPin,OUTPUT);

  Serial.begin(115200);
}
void loop() {

  move(stepPin,dirPin, -1,3000);
  delay(1000);
  move(stepPin,dirPin, 1,3000);
  delay(1000);
}


void move(int stepPin,int dirPin, int direction, int nb_step){


  if(direction>0){

    digitalWrite(dirPin,HIGH); 

    for(int x = 0; x < nb_step; x++) {

    digitalWrite(stepPin,HIGH); 
    delayMicroseconds(DELAY);    // by changing this time delay between the steps we can change the rotation speed
    digitalWrite(stepPin,LOW); 
    delayMicroseconds(DELAY); 
    Serial.println(x);
    
    }
  }

  else{

    digitalWrite(dirPin,LOW); 

    for(int x = 0; x < nb_step; x++) {

    digitalWrite(stepPin,HIGH); 
    delayMicroseconds(DELAY);    // by changing this time delay between the steps we can change the rotation speed
    digitalWrite(stepPin,LOW); 
    delayMicroseconds(DELAY);
    Serial.println(x);
    }
 
  }
   

}