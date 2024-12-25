#define switch 2
int set = 0;
int index = 0;

int** arr = new int*[6]];  // Create an array of pointers (one for each row)
for (int i = 0; i < 6; ++i) {
  arr[i] = new int[600];  // Allocate memory for each column in the row
}

int[] zeros;
for(int i = 0; i < 600; i++){
  zeros[i] = 0;
}


//counts sets and keeps light on during sampling period
int setCounter{
  if(digitalRead(switch) == HIGH){
    set++;
    digitalWrite(switch, HIGH); // Turn LED on
    delay(30000); // Wait for 15 seconds
    digitalWrite(switch, LOW); // Turn LED off // also turns switch off for next set  
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
  if(digitalRead(Oswitch) == HIGH){
    if(millis() < 30000){
      if(index < 600){
        arr[index][0] = analogRead(A0);
        arr[index][1] = analogRead(A1);
        arr[index][2] = analogRead(A2);
        arr[index][3] = analogRead(A3);
        arr[index][4] = analogRead(A4);
        arr[index][5] = analogRead(A5);
        index++
        delay(50);
      }
    }
    else{
      right = arr[0];
      right1 = arr[1];
      right2 = arr[2];
      left = arr[3];
      left1 = arr[4];
      left2 = arr[5];
      // apply fourier transform to each row 
\      // store in SD card 
      // clear array 
    }
  }
}
