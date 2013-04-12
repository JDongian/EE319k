#include "ADC.h"
//Variables
double zeroVoltage;
double maxVoltage;
double scaleFactor;

void ADCInit(void){
	zeroVoltage = 0;
	maxVoltage = 5;
	scaleFactor = 2.0/(maxVoltage-zeroVoltage);
}

double getVoltage(void){
	
	return 0;
}

void setZero(void){
	zeroVoltage = getVoltage();
	scaleFactor = 2.0/(maxVoltage-zeroVoltage);
}

void setMax(void){
	maxVoltage = getVoltage();
	scaleFactor = 2.0/(maxVoltage-zeroVoltage);
}

double getLength(int voltage){
	return (getVoltage()-zeroVoltage)*scaleFactor;
}
