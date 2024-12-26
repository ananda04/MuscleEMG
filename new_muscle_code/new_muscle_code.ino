#define switch 2
#include <stdio.h>
#include <math.h>
#include "CComplex.h"

#define PI 3.14159265358979323846

int set = 0;
int index = 0;

// int[] zeros;
// for(int i = 0; i < 600; i++){
//   zeros[i] = 0;
// }


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
void fft(Complex double *x, int N){
  if (N <= 1) return;

  complex double *even = malloc(N / 2 * sizeof(complex double));
  complex double *odd = malloc(N / 2 * sizeof(complex double));

  for (int i = 0; i < N / 2; i++) {
      even[i] = x[2 * i];
      odd[i] = x[2 * i + 1];
  }

  fft(even, N / 2);
  fft(odd, N / 2);

  for (int k = 0; k < N / 2; k++) {
    complex double t = cexp(-I * 2 * PI * k / N) * odd[k];
    x[k] = even[k] + t;
    x[k + N / 2] = even[k] - t;
  }

  free(even);
  free(odd);

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

  int** arr = new int*[6];  // Create an array of pointers (one for each row)
  for (int i = 0; i < 6; i++) {
    arr[i] = new int[600];  // Allocate memory for each column in the row
  }
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
      for(int i = 0;i<600;i++){
        arr[0][i] = fft(arr[0][i], 600).mag();
        arr[1][i] = fft(arr[1][i], 600).mag();
        arr[2][i] = fft(arr[2][i], 600).mag();
        arr[3][i] = fft(arr[3][i], 600).mag();
        arr[4][i] = fft(arr[4][i], 600).mag();
        arr[5][i] = fft(arr[5][i], 600).mag();
      }
      
      // apply fourier transform to each row 
      // store in SD card 
      // clear array 
    }
  }
}
