
int previous = 0;
int stepPin =16;
int dirPin = 17;
int delta_step=0;
int val = 0;
int nb_step =0;


#define DELAY 200

void setup() {
  // put your setup code here, to run once:

  pinMode(stepPin,OUTPUT); 
  pinMode(dirPin,OUTPUT);
  pinMode(A0,INPUT);
  Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:

  val = analogRead(A0);
  delta_step= val-previous;
  previous=val;
  nb_step=abs(delta_step);


  if(delta_step<0){    
    

    for(int x = 0; x < nb_step; x++) {

    digitalWrite(dirPin,HIGH); 

    digitalWrite(stepPin,HIGH); 
    delayMicroseconds(DELAY);
    digitalWrite(stepPin,LOW); 
    delayMicroseconds(DELAY);
    
    }
    
    Serial.println("CLK FIN");
   
  }

  if(delta_step>0){

    for(int x = 0; x < nb_step; x++) {

    digitalWrite(dirPin,LOW);

    digitalWrite(stepPin,HIGH); 
    delayMicroseconds(DELAY);    // by changing this time delay between the steps we can change the rotation speed
    digitalWrite(stepPin,LOW); 
    delayMicroseconds(DELAY); 

    }
    Serial.println("-----------------------------------------ANTI CLK FIN");  
   
  }


}
