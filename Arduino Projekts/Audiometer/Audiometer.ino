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
LedControl lc = LedControl(DIN,CLK,CS,1);
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
  setLedLevel(ledLevelLeft, ledLevelRight);
  delay(100);
}
void setLedLevel(int levelLeft, int levelRight){
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
