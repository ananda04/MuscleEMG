#include <SD.h>
#include <SPI.h>
File myFile;

const int Oswitch = 2;
int mLeft;
int mRight;
bool count = false;



void setup() {
  Serial.begin(9600);
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);
  pinMode(A4, INPUT);
  pinMode(A5, INPUT);
  pinMode(2, INPUT);
  digitalWrite(2, HIGH);
}

void loop() {
  if(digitalRead(Oswitch) == HIGH){
    mRight = (analogRead(A0)+analogRead(A1)+analogRead(A2))/3;
    mLeft = (analogRead(A3)+analogRead(A4)+analogRead(A5))/3;
    //Serial.println("Min:0,Max:1023");    
    myFile.print((mRight);
    myFile.print(",");
    myFile.println(mLeft);
    

  }
  if(digitalRead(Oswitch) == LOW){
    count = true; 
    newSet(count);
    pause();
  }

  }

void newSet(bool count){
  if (count == true){
    Serial.println("New Set");
  }
}
void pause(){
    if(digitalRead(Oswitch) == LOW){
    }
}


  




