#include <LedControl.h>
#include <Grove_LED_Bar.h>
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
const int barLedCount = 10;
/*Declare Variables*/
int threshold = -1;/*Threshold is powerSupply/2 --> calcukation in setup()*/
int sensorValueLeft;
int sensorValueRight;
int absValueLeft;
int absValueRight;
int matrixLevelLeft;
int matrixLevelRight;
int barLevelLeft;
int barLevelRight;
/*Pins*/
int audioSensorLeft = A1;
int audioSensorRight = A0;
int matrixDIN = 2;
int matrixCS = 3;
int matrixCLK = 4;
int barLeftDIN = 5;
int barLeftData = 6;
int barLeftCLK = 7;
int barRightDIN = 8;
int barRightData = 9;
int barRightCLK = 10;
LedControl lc = LedControl(matrixDIN,matrixCLK,matrixCS,1);
Grove_LED_Bar barLeft(barLeftCLK, barLeftDIN, barLeftData, LED_BAR_10); // Clock pin, Data pin, Orientation
Grove_LED_Bar barRight(barRightCLK, barRightDIN, barRightData, LED_BAR_10); // Clock pin, Data pin, Orientation
int i = 0;
int k = 0;
int countI = 0;
int countK = 0;

void setup() {
  Serial.begin(9600);
  /*Setup Audio Input Sensors*/
  pinMode(audioSensorLeft, INPUT);
  pinMode(audioSensorRight, INPUT);
  /*Threshold calc(threshold is always vcc/2)*/
  threshold = (vccSoundSupply/(vccADC/adcResolution))/2;
  /*Setup LED matrix*/ 
  lc.shutdown(0,false);
  // Set brightness to a medium value
  lc.setIntensity(0,8);
  // Clear the display
  lc.clearDisplay(0);
  barLeft.begin();
  barRight.begin();
  barLeft.setBits(0x0);
  barRight.setBits(0x0);
}
void loop() {
  sensorValueLeft = analogRead(audioSensorLeft);
  sensorValueRight = analogRead(audioSensorRight);
  absValueLeft = abs(sensorValueLeft - threshold);
  absValueRight = abs(threshold - sensorValueRight);
  matrixLevelLeft = map(absValueLeft, 0, highestADCValue, 0, ledCount);
  matrixLevelRight = map(absValueRight, 0, highestADCValue, 0, ledCount);
  barLevelLeft = map(absValueLeft, 0, highestADCValue, 0, barLedCount);
  barLevelRight = map(absValueRight, 0, highestADCValue, 0, barLedCount);
  //Serial.print(threshold);
  //Serial.print(" ");
  //Serial.print(sensorValueRight);
  //Serial.print(" ");
  Serial.println(absValueRight);
  //Serial.println(ledLevelRight);
  setMatrixLevel(matrixLevelLeft, matrixLevelRight);
  setMatrixLevel(barLevelLeft, barLevelRight);
  
}
void setMatrixLevel(int levelLeft, int levelRight){
  barLevelLeft.setBits((2^levelLeft)-1);
  barLevelRight.setBits((2^levelRight)-1);
  
}
void setLMatrixLevel(int levelLeft, int levelRight){
   lc.clearDisplay(0);
  /*Row 0-3 belong to Right Sensor, Row 4-7 belong to Left Sensor*/
  if (levelRight >= 1){
    lc.setRow(0, 3, B00011000);
  }
  if (levelLeft >= 1){
    lc.setRow(0, 4, B00011000);
  }
  if (levelRight >= 2){
    lc.setRow(0, 3, B00111100);
    lc.setRow(0, 2, B00111100);
  }
  if (levelLeft >= 2){
    lc.setRow(0, 4, B00111100);
    lc.setRow(0, 5, B00111100);
  }
  if (levelRight >= 3){
    lc.setRow(0, 3, B01111110);
    lc.setRow(0, 2, B01111110);
    lc.setRow(0, 1, B01111110);
  }
  if (levelLeft >= 3){
    lc.setRow(0, 4, B01111110);
    lc.setRow(0, 5, B01111110);
    lc.setRow(0, 6, B01111110);
  }
  if (levelRight >= 4){
    lc.setRow(0, 3, B11111111);
    lc.setRow(0, 2, B11111111);
    lc.setRow(0, 1, B11111111);
    lc.setRow(0, 0, B11111111);
  }
  if (levelLeft >= 4){
    lc.setRow(0, 4, B11111111);
    lc.setRow(0, 5, B11111111);
    lc.setRow(0, 6, B11111111);
    lc.setRow(0, 7, B11111111);
  }
}
