#include "ADC.h"

void ADCInit(void){
	zeroVoltage = 0;
	maxVoltage = 5;
	scaleFactor = (maxVoltage-zeroVoltage)/2.0;
}

double getVoltage(void){
	
	return 0;
}

void setZero(void){
	zeroVoltage = getVoltage();
	scaleFactor = (maxVoltage-zeroVoltage)/2.0;
}

void setMax(void){
	maxVoltage = getVoltage();
	scaleFactor = (maxVoltage-zeroVoltage)/2.0;
}

double getLength(int voltage){
	return (getVoltage()-zeroVoltage)*scaleFactor;
}


