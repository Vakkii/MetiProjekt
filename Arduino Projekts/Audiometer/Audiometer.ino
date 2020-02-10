#include <LedControl.h>

/*
Audiometer with Arduino UNO, GY-MAX4466 and  a 8x8 LED Matrix
Author: Lukas Bertsch, Lukas.Bertsch@Student.Reutlingen-University.de
last modified on 27.01.2020
*/
/*Define Constants*/
const float vccADC = 5.0;/*5V max supply which the adc is using*/
const float adcResolution = 1024;/*10 bit ADC*/
const float vccSoundSupply = 3.3;/*Soundsensor uses 3.3 V power supply*/
const int highestADCValue = 350;
const int ledCount = 4; //number of LED Levels on the maxtrix
/*Declare Variables*/
int threshold = -1;/*Threshold is powerSupply/2 --> calcukation in setup()*/
int sensorValueLeft;
int sensorValueRight;
int absValueLeft;
int absValueRight;
int ledLevelLeft;
int ledLevelRight;
/*Pins*/
int audioSensorLeft = A1;
int audioSensorRight = A0;
int CS = 3;
int DIN = 2;
int CLK = 4;

int i = 0;
int k = 0;
int countI = 0;
int countK = 0;
byte hf[8]= {B00111100,B01000010,B10100101,B10000001,B10100101,B10011001,B01000010,B00111100};

void setup() {
  Serial.begin(9600);
  /*Setup Audio Input Sensors*/
  pinMode(audioSensorLeft, INPUT);
  pinMode(audioSensorRight, INPUT);
  /*Threshold calc(threshold is always vcc/2)*/
  threshold = (vccSoundSupply/(vccADC/adcResolution))/2;
  /*Setup LED matrix*/
  LedControl lc =LedControl(DIN,CLK,CS,1);
    lc.shutdown(0,false);
  // Set brightness to a medium value
  lc.setIntensity(0,8);
  // Clear the display
  lc.clearDisplay(0);
    lc.setRow(0,0,hf[0]);
  lc.setRow(0,1,hf[1]);
  lc.setRow(0,2,hf[2]);
  lc.setRow(0,3,hf[3]);
  lc.setRow(0,4,hf[4]);
  lc.setRow(0,5,hf[5]);
  lc.setRow(0,6,hf[6]);
  lc.setRow(0,7,hf[7]);
  //resetAll();
  
}
void loop() {
  sensorValueLeft = analogRead(audioSensorLeft);
  sensorValueRight = analogRead(audioSensorRight);
  absValueLeft = abs(sensorValueLeft - threshold);
  absValueRight = abs(threshold - sensorValueRight);
  ledLevelLeft = map(absValueLeft, 0, highestADCValue, 0, ledCount);
  ledLevelRight = map(absValueRight, 0, highestADCValue, 0, ledCount);
  //Serial.print(threshold);
  //Serial.print(" ");
  //Serial.print(sensorValueRight);
  //Serial.print(" ");
  Serial.println(absValueRight);
  //Serial.println(ledLevelRight);
  //setLedLevel(ledLevelLeft, ledLevelRight);
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
  //digitalWrite(rows[row], HIGH);
  //digitalWrite(cols[col], LOW);
}
void resetAll(){
    for (volatile int i = 0; i <= 7; i++){
     // digitalWrite(cols[i], HIGH);
      //digitalWrite(rows[i], LOW);
    
  }
}
