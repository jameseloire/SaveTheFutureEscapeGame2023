#include <Encoder.h>
#include <LiquidCrystal_I2C.h>


// set the LCD number of columns and rows
int lcdColumns = 16;
int lcdRows = 2;
LiquidCrystal_I2C lcd(0x27, lcdColumns, lcdRows);  



Encoder knobLeft(32, 33);
Encoder knobMid(25, 26);
Encoder knobRight(27, 14);


void setup() {
  Serial.begin(9600);
  lcd.init();                   
  lcd.backlight();
  Serial.println(" Encoder Test:");
  lcd.print("Save The Futur !");
  delay(3000);
}

long positionLeft  = -999;
long positionRight = -999;
long positionMid = -999;

void loop() {



  long newLeft, newRight, newMid;
  newLeft = knobLeft.read();
  newRight = knobRight.read();
  newMid = knobMid.read();
  
  if (newLeft != positionLeft || newRight != positionRight || newMid != positionMid) {

    Serial.print("Left = ");
    Serial.println(newLeft);
    Serial.print(", Mid = ");
    Serial.println(newMid);
    Serial.print(", Right = ");
    Serial.println(newRight);
    Serial.println();

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("X: ");
    lcd.print(String(newLeft));
    lcd.print("  Y: "); 
    lcd.print(String(newMid));
    lcd.setCursor(0, 1);
    lcd.print("Z: ");
    lcd.print(String(newRight));


    positionLeft = newLeft;
    positionRight = newRight;
    positionMid = newMid;
  }
  // if a character is sent from the serial monitor,
  // reset both back to zero.
  if (Serial.available()) {
    Serial.read();
    Serial.println("Reset both knobs to zero");
    knobLeft.write(0);
    knobRight.write(0);
    knobMid.write(0);
  }
}