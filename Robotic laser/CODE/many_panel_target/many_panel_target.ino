
//100LED 8*panel and targets ring led  Please save me form the furture doesn't look good here :/
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>  // Required for 16 MHz Adafruit Trinket
#endif


#define PIN1 2 /
#define PIN2 3 
#define PIN3 4 
#define PIN4 5 
#define PIN5 6 
#define PIN6 7 
#define PIN7 8 
#define PIN8 9 



#define NUMPIXELS 100  
#define NUMSTRIP 8
Adafruit_NeoPixel pixel[NUMSTRIP] = {

Adafruit_NeoPixel(NUMPIXELS, PIN1, NEO_GRB + NEO_KHZ800),
Adafruit_NeoPixel(NUMPIXELS, PIN2, NEO_GRB + NEO_KHZ800),
Adafruit_NeoPixel(NUMPIXELS, PIN3, NEO_GRB + NEO_KHZ800),
Adafruit_NeoPixel(NUMPIXELS, PIN4, NEO_GRB + NEO_KHZ800),
Adafruit_NeoPixel(NUMPIXELS, PIN5, NEO_GRB + NEO_KHZ800),
Adafruit_NeoPixel(NUMPIXELS, PIN6, NEO_GRB + NEO_KHZ800),
Adafruit_NeoPixel(NUMPIXELS, PIN7, NEO_GRB + NEO_KHZ800),
Adafruit_NeoPixel(NUMPIXELS, PIN8, NEO_GRB + NEO_KHZ800)

};

int target[NUMSTRIP]={A0,A1,A2,A3,A4,A5,A6,A7};
int statetarget[NUMSTRIP]={0,0,0,0,0,0,0,0};


#define DELAYVAL 50  // Time (in milliseconds) to pause between pixels

void setup() {
  
  for (int i = 0; i < NUMSTRIP; i++) {
    
    pixel[i].begin();
    pixel[i].clear();
  }


}

void loop() {

  for (int strip = 0; strip < NUMSTRIP; strip++) {

    pixel[strip].clear();

    for (int i = 0; i < NUMPIXELS; i++) {  // For each pixel...

      pixel[strip].setPixelColor(i, pixel[strip].Color(200, 150, 100));

      pixel[strip].show(); 

      delay(DELAYVAL);  
    }

    checkTarget(target[strip], 300);

  }

  
  

  
}

void checkTarget(int num, int threshold){

  if(digitalRead(num)<threshold){
    statetarget[num]=1;

    for (int i = 0; i < NUMPIXELS; i++) {  // For each pixel...

      // pixels.Color() takes RGB values, from 0,0,0 up to 255,255,255
      // Here we're using a moderately bright green color:
      pixel[num].setPixelColor(i, pixel[num].Color(255, 0, 0));

      pixel[num].show();  // Send the updated pixel colors to the hardware.

      delay(DELAYVAL);  // Pause before next pass through loop
    }
  }

}





