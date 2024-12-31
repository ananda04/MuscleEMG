#define switch 2
#include <stdio.h>
#include <math.h>
#include "CComplex.h"
#include <SD.h>
#include <SPI.h>

#define PI 3.14159265358979323846

int set = 0;
int index = 0;

//DFT setup
long real[6][600];
long img[6][600];
long mag[6][600];

//input signal setup
long arr[6][600];

//SD card set up
File myFile;

//counts sets and keeps light on during sampling period
int setCounter(){
  if(digitalRead(switch) == HIGH){
    set++;
    digitalWrite(switch, HIGH); // Turn LED on
    delay(30000); // Wait for 15 seconds
    digitalWrite(switch, LOW); // Turn LED off // also turns switch off for next set  
  }
}

// fft algorithm using Cooley-Tukey algorithm
// implementation is incorrect need to fix this 
void computeDFT(int row){
  // apply fourier transform to each row 
  for(int i = 0; i < 600; i++){ // frequency bins
    for(int j = 0; j<600;j++){ // time sampling
      float angle = 2 * PI * i * j/600;
      mag[row][j] = sqrt((arr[i][j] * cos(angle) * arr[i][j] * cos(angle)) + (arr[i][j] * sin(angle) * arr[i][j] * sin(angle)));
    }
  }
}


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);
  pinMode(A4, INPUT);
  pinMode(A5, INPUT);
  pinMode(2, INPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  if(digitalRead(switch) == HIGH){
    if(millis() < 30000){
      if(index < 600){
        arr[0][index] = analogRead(A0);
        arr[1][index] = analogRead(A1);
        arr[2][index] = analogRead(A2);
        arr[3][index] = analogRead(A3);
        arr[4][index] = analogRead(A4);
        arr[5][index] = analogRead(A5);
        index++;
        delay(50);
      }
    }
    else{
      for(int i =0; i<6;i++){
        computeDFT(i);
      }
    
      // store in SD card 
      myFile = SD.open("test.txt", FILE_WRITE);

      // if the file opened okay, write to it:
      if (myFile) {
        for(int i = 0;i<600;i++){
          myFile.print(mag[0][i]);
          myFile.print(",");
          myFile.print(mag[1][i]);
          myFile.print(",");
          myFile.print(mag[2][i]);
          myFile.print(",");
          myFile.print(mag[3][i]);
          myFile.print(",");
          myFile.print(mag[4][i]);
          myFile.print(",");
          myFile.println(mag[5][i]);
        }
        // close the file:
        myFile.close();
        Serial.println("done.");
      } else {
        // if the file didn't open, print an error:
        Serial.println("error opening test.txt");
      }
      // clear array 
    }
  }
}
