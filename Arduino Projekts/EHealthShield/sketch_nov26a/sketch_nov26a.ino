#include <PinChangeInt.h>
#include <PinChangeIntConfig.h>
#include <eHealth.h>
#include <eHealthDisplay.h>
int count = 0;
int pulse;
int oxy;
double temperature;
  int systolic = 0;
  int diastolic = 0;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  eHealth.readPulsioximeter();
  PCintPort::attachInterrupt(6, readPulsioximeter, RISING);
  eHealth.initPositionSensor();
  count = 0;

  
  
}

void loop() {
  // put your main code here, to run repeatedly:
  pulse = eHealth.getBPM();
  oxy = eHealth.getOxygenSaturation();
  temperature = (double)eHealth.getTemperature();
  uint8_t position = eHealth.getBodyPosition();
  String posi = getPositionFromInt(position);
  float ECG = eHealth.getECG();
  float conductance = eHealth.getSkinConductanceVoltage();

  Serial.print("temperature");
  Serial.print("=");
  Serial.print(temperature);
  Serial.print("=");
  Serial.print("pulse");
  Serial.print("=");
  Serial.print(pulse);
  Serial.print("=");
  Serial.print("oxy");
  Serial.print("=");
  Serial.print(oxy);
  Serial.print("=");
  Serial.print("position");
  Serial.print("=");
  Serial.print(posi);
  Serial.print("=");
  Serial.print("ecg");
  Serial.print("=");
  Serial.print(ECG, 2);
  Serial.print("=");
  Serial.print("bpSys");
  Serial.print("=");
  Serial.print(systolic);
    Serial.print("=");
  Serial.print("bpDias");
  Serial.print("=");
  Serial.print(diastolic);
  Serial.print("=");
  Serial.print("conductance");
  Serial.print("=");
  Serial.print(conductance);
  Serial.print("$");

}
String getPositionFromInt(uint8_t position){
  		if (position == 1) {
			return("Supine position");    
		} else if (position == 2) {
			return("Left lateral decubitus");
		} else if (position == 3) {
			return("Rigth lateral decubitus");
		} else if (position == 4) {
			return("Prone position");
		} else if (position == 5) {
			return("Stand or sit position");
		} else  {
			return("non-defined position");
		}
}
void readPulsioximeter(){
  count ++;
  if (count == 50) { //Get only one 50 measures to reduce the latency
    eHealth.readPulsioximeter();
    count = 0;
  }
}
