/*
Audiometer with Arduino UNO, KY-37 and  a 8x8 LED Matrix
Author: Lukas Bertsch, Lukas.Bertsch@Student.Reutlingen-University.de
last modified on 27.01.2020
*/
/*Define Constants*/;
const int thresholdLeft = 522; //Enter Your threshold value here
const int thresholdRight = 510; //Enter Your threshold value here
const int ledCount = 4; //number of LED Levels
/*Declare Variables*/
int sensorValueLeft;
int sensorValueRight;
int absValueLeft;
int absValueRight;
int ledLevelLeft;
int ledLevelRight;
/*Pins*/
int cols[] = {2, 3, 4, 5, 6, 7, 8, 9}; // matrix pins
int rows[] = {10, 11, 12, 13, A2, A3, A4, A5}; // matrix pins
int audioSensorLeft = A1;
int audioSensorRight = A0;

int i = 0;
int k = 0;
int countI = 0;
int countK = 0;
void setup() {
  Serial.begin(9600);
  /*Setup Audio Input Sensors*/
  pinMode(audioSensorLeft, INPUT);
  pinMode(audioSensorRight, INPUT);
  /*Setup LED matrix*/
  for (volatile int i = 0; i <= 7; i++){ // Define matrix pins OUTPUT
    pinMode(rows[i], OUTPUT);
    pinMode(cols[i], OUTPUT);
  }
  resetAll();
  
}
void loop() {
  sensorValueLeft = analogRead(audioSensorLeft);
  sensorValueRight = analogRead(audioSensorRight);
  absValueLeft = abs(sensorValueLeft - thresholdLeft);
  absValueRight = abs(sensorValueRight - thresholdRight);
  ledLevelLeft = map(absValueLeft, 0, (1024 - thresholdLeft)/(1.75), 0, ledCount);
  ledLevelRight = map(absValueRight, 0, (1024 - thresholdRight)/(1.75), 0, ledCount);
  Serial.print(ledLevelLeft);
  Serial.print(" ");
  Serial.println(ledLevelRight);
  setLedLevel(ledLevelLeft, ledLevelRight);
}

void setLedLevel(int levelLeft, int levelRight){
  /*Reset*/
  resetAll();
  /*Set Left Half*/
  if(levelLeft >= 1){
    turnOnLed(3,3);
    resetAll();
    turnOnLed(3,4);
    resetAll();

  }
  if(levelLeft >= 2){
    turnOnLed(3,2);
    resetAll();
    turnOnLed(3,5);
    resetAll();
    turnOnLed(2,2);
    resetAll();
    turnOnLed(2,3);
    resetAll();
    turnOnLed(2,4);
    resetAll();
    turnOnLed(2,5);
    resetAll();
  }
  if(levelLeft >= 3){
    turnOnLed(3,1);
    resetAll();
    turnOnLed(3,6);
    resetAll();
    turnOnLed(2,1);
    resetAll();
    turnOnLed(2,6);
    resetAll();
    turnOnLed(1,1);
    resetAll();
    turnOnLed(1,2);
    resetAll();
    turnOnLed(1,3);
    resetAll();
    turnOnLed(1,4);
    resetAll();
    turnOnLed(1,5);
    resetAll();
    turnOnLed(1,6);
    resetAll();
  }
  if(levelLeft >= 4){
    turnOnLed(3,0);
    resetAll();
    turnOnLed(3,7);
    resetAll();
    turnOnLed(2,0);
    resetAll();
    turnOnLed(2,7);
    resetAll();
    turnOnLed(1,0);
    resetAll();
    turnOnLed(1,7);
    resetAll();
    turnOnLed(0,0);
    resetAll();
    turnOnLed(0,1);
    resetAll();
    turnOnLed(0,2);
    resetAll();
    turnOnLed(0,3);
    resetAll();
    turnOnLed(0,4);
    resetAll();
    turnOnLed(0,5);
    resetAll();
    turnOnLed(0,6);
    resetAll();
    turnOnLed(0,7);
    resetAll();
  }
  /*Set Right Half*/
  if(levelRight >= 1){
    turnOnLed(4,3);
    resetAll();
    turnOnLed(4,4);
    resetAll();
  }
  if(levelRight >= 2){
    turnOnLed(4,2);
    resetAll();
    turnOnLed(4,5);
    resetAll();
    turnOnLed(5,2);
    resetAll();
    turnOnLed(5,3);
    resetAll();
    turnOnLed(5,4);
    resetAll();
    turnOnLed(5,5);
    resetAll();
  }
  if(levelRight >= 3){
    turnOnLed(4,1);
    resetAll();
    turnOnLed(4,6);
    resetAll();
    turnOnLed(5,1);
    resetAll();
    turnOnLed(5,6);
    resetAll();
    turnOnLed(6,1);
    resetAll();
    turnOnLed(6,2);
    resetAll();
    turnOnLed(6,3);
    resetAll();
    turnOnLed(6,4);
    resetAll();
    turnOnLed(6,5);
    resetAll();
    turnOnLed(6,6);
    resetAll();
  }
  if(levelRight >= 4){
    turnOnLed(4,0);
    resetAll();
    turnOnLed(4,7);
    resetAll();
    turnOnLed(5,0);
    resetAll();
    turnOnLed(5,7);
    resetAll();
    turnOnLed(6,0);
    resetAll();
    turnOnLed(6,7);
    resetAll();
    turnOnLed(7,0);
    resetAll();
    turnOnLed(7,1);
    resetAll();
    turnOnLed(7,2);
    resetAll();
    turnOnLed(7,3);
    resetAll();
    turnOnLed(7,4);
    resetAll();
    turnOnLed(7,5);
    resetAll();
    turnOnLed(7,6);
    resetAll();
    turnOnLed(7,7);
    resetAll();
  }
  
  
}
void turnOnLed(int col, int row){
  digitalWrite(rows[row], HIGH);
  digitalWrite(cols[col], LOW);
}
void resetAll(){
    for (volatile int i = 0; i <= 7; i++){
      digitalWrite(cols[i], HIGH);
      digitalWrite(rows[i], LOW);
    
  }
}
