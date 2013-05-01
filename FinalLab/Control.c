#include "Control.h"

int controlStatus = 0;
int avgX=0, currX=0;
int avgY=0, currY=0;
bool selectSamples[SELECT_SAMPLES];
short currSelectIndex = 0;

bool isControlActivated(short ctrlKey){
	if(controlStatus & 1<<ctrlKey == True) {
		return True;
	} return False;
}
void portD_Init(void){
	SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOD;
	doNothing();
	GPIO_PORTD_DIR_R &= ~0x01;
	GPIO_PORTD_AFSEL_R |= 0x00;
	GPIO_PORTD_PUR_R |= 0x00;
	GPIO_PORTD_DEN_R |= 0x01;
}
char get_portD(char bit){
	char ans = GPIO_PORTD_DATA_R;
	ans = (ans>>bit);
	ans &= 0x01;
	return ans;
}
void setControl(bool status, short ctrlKey) {
	if(status == True) {
		controlStatus |= 1<<ctrlKey;
	} else {
		controlStatus &= 0xFFFF-1<<ctrlKey;
	}
}
void setXYAvg(void) {
	avgX = currX;
	avgY = currY;
}/*
bool isControlActivated(short ctrlKey){
	if(controlStatus & 1<<ctrlKey == True) {
		return True;
	} return False;
}*/
void updateXAxis(void) {
	short sum=0, i=0;
	//if(ADCStatus0 == 0) { return; }
	//currX = (currX*63+ADC_In0())/64;
	if(currX < avgX-ANALOG_THRESHOLD) {
		setControl(True, ANALOG_LEFT);
		setControl(False, ANALOG_RIGHT);
	} else if(avgX+ANALOG_THRESHOLD < currX) {
		setControl(True, ANALOG_RIGHT);
		setControl(False, ANALOG_LEFT);
	} else {
		setControl(False, ANALOG_LEFT);
		setControl(False, ANALOG_RIGHT);
	}
	//Select button
	//	selectSamples[currSelectIndex] = port D;
	currSelectIndex = (currSelectIndex+1)%SELECT_SAMPLES;
	for(i = 0; i < SELECT_SAMPLES; i++) {
		if(selectSamples[i] == True) {
			sum++;
		}
	}
	if(sum > SELECT_SAMPLES/2) {
		setControl(True, SELECT);
	} else {
		setControl(True, SELECT);
	}
}
void updateYAxis(void) {
	short sum=0, i=0;
	//if(ADCStatus1 == 0) { return; }
	//currY = (currY*63+ADC_In1())/64;
	//Y axis
	if(currY < avgY-ANALOG_THRESHOLD) {
		setControl(True, ANALOG_DOWN);
		setControl(False, ANALOG_UP);
	} else if(avgY+ANALOG_THRESHOLD < currY) {
		setControl(True, ANALOG_UP);
		setControl(False, ANALOG_DOWN);
	} else {
		setControl(False, ANALOG_DOWN);
		setControl(False, ANALOG_UP);
	}
	//Select button
	//	selectSamples[currSelectIndex] = port D;
	currSelectIndex = (currSelectIndex+1)%SELECT_SAMPLES;
	for(i = 0; i < SELECT_SAMPLES; i++) {
		if(selectSamples[i] == True) {
			sum++;
		}
	}
	if(sum > SELECT_SAMPLES/2) {
		setControl(True, SELECT);
	} else {
		setControl(True, SELECT);
	}
}
void portD_Handler(void) {
	HWREGBITW(&gFlags, SELECT_DOWN) = 0;
	if ((GPIO_PORTD_MIS_R & 0x01)) {
		HWREGBITW(&gFlags, SELECT_DOWN) = 1;
	}
}
