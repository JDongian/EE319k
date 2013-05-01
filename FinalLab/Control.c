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
void portD_Init(void) {
	SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOD;
	doNothing();
	GPIO_PORTD_DIR_R &= 0x00;
	GPIO_PORTD_AFSEL_R |= 0x00;
	GPIO_PORTD_PUR_R |= 0x00;
	GPIO_PORTD_DEN_R |= 0xFF;
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
}
void updateControls(void) {
	short sum=0, i=0;
	currX = (currX*63+getADC0Value())/64;
	currY = (currY*63+getADC0Value())/64;
	currSelectIndex = (currSelectIndex+1)%SELECT_SAMPLES;
//	selectSamples[currSelectIndex] = port D;
	//X axis
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

