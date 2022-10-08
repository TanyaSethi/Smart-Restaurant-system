#include<LiquidCrystal.h>
int Contrast=30;
LiquidCrystal lcd(10,3,8,9,12,11);
int state;
int buttonState = 0;  
const int buttonPin = 2;
int flag=0;       
void stp();
void fwd();
void setup()
{
    analogWrite(6,Contrast);
    lcd.begin(16,2);
    pinMode(7,OUTPUT);                 
    pinMode(8,OUTPUT);                  
    pinMode(5,OUTPUT);                  
    pinMode(6,OUTPUT); 
    pinMode(13, OUTPUT);        
    pinMode(buttonPin, INPUT);  
    Serial.begin(9600);                                             
}
void loop() {
    lcd.setCursor(0,0);
    lcd.print("Welcome");
    buttonState = digitalRead(buttonPin);

  // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
  if (buttonState == LOW) { 
    lcd.clear(); 
    lcd.setCursor(0,8);
    lcd.print("Order Ready!");
    fwd();
    Serial.print("button pressed");
    delay(1000);
    lcd.clear();
    lcd.setCursor(0,8);
    lcd.print("Your order has been Delivered.");
    delay(1000);
  } else {
   lcd.setCursor(0,0);
   // lcd.print("Welcome");
    Serial.print(".....removed");
    stp();
  }
  
}                                           //loop() ends here

void fwd()          // Forward
{
  digitalWrite(7,HIGH);
  digitalWrite(5,HIGH);
  digitalWrite(6,LOW);
  digitalWrite(8,LOW);
  digitalWrite(13, HIGH);
}

void stp()            // Robot STops
{
  digitalWrite(7,LOW);
  digitalWrite(8,LOW);
  digitalWrite(5,LOW);
  digitalWrite(6,LOW);
  digitalWrite(13, LOW);
}


