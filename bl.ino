#include<SoftwareSerial.h>
#include <Servo.h>
SoftwareSerial mySerial(10,11);
Servo myservo;
int pos = 0;
int calibrationTime = 10;
long unsigned int lowIn;
long unsigned int pause = 50;
boolean lockLow = true;
boolean takeLowTime;
char val;
int pirPin = 12; 

void setup()
{
  myservo.attach(9);
  pinMode(2,OUTPUT);
  pinMode(6,OUTPUT);
  pinMode(7,OUTPUT);
  pinMode(5,OUTPUT);
  Serial.begin(9600);
  mySerial.begin(38400);
  pinMode(pirPin, INPUT);
 pinMode(9,OUTPUT);
  digitalWrite(pirPin, LOW);
  for(int i = 0; i < calibrationTime; i++) {
  Serial.print(".");
  }
}
void loop(){
  //PIR and Gate_servo motor
  if(digitalRead(pirPin) == HIGH){
  //Serial.print("Motion Detected");
  for (pos = 0; pos <= 120; pos += 2) { 
        myservo.write(pos);   
        delay(50);          
    }
if(lockLow){

//makes sure we wait for a transition to LOW before any further output is made:

lockLow = false;

}

takeLowTime = true;

}
if(digitalRead(pirPin) == LOW){
 // digitalWrite(9, LOW);
  for (pos = 120; pos <= 0;pos -= 2) {
      myservo.write(pos);      
      delay(50);                       
  }
 //the led visualizes the sensors output pin state

if(takeLowTime){

lowIn = millis(); //save the time of the transition from high to LOW

takeLowTime = false; //make sure this is only done at the start of a LOW phase

}

//if the sensor is low for more than the given pause,

//we assume that no more motion is going to happen

if(!lockLow && millis() - lowIn > pause){

//makes sure this block of code is only executed again after

//a new motion sequence has been detected

lockLow = true;

Serial.print("motion ended"); //output

//delay(50);

}

}
//bluetooth
  if (mySerial.available()) {
    Serial.write(val=mySerial.read());
    Serial.read();
    if(val =='1')
    {
      if(digitalRead(2)==LOW)
       digitalWrite(2,HIGH);
      else
       digitalWrite(2,LOW);
    }
    if(val =='2')
    {
      if(digitalRead(5)==LOW)
      digitalWrite(5,HIGH);
      else
      digitalWrite(5,LOW);
    }
    if(val == '3')
    {
      if(digitalRead(6)==LOW)
      digitalWrite(6,HIGH);
      else
      digitalWrite(6,LOW);
    }
       
    if(val == '4')
    {
      if(digitalRead(7)==LOW)
      digitalWrite(7,HIGH);
      else
      digitalWrite(7,LOW);
    }
  }
}


