#include "Control.h"

int controlStatus = 0;
int avgX=0, currX=0;
int avgY=0, currY=0;
bool selectSamples[SELECT_SAMPLES];
short currSelectIndex = 0;


void portD_Init(void){
	SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOD;
	doNothing();
	GPIO_PORTD_DIR_R &= ~0x0F;
  GPIO_PORTD_DEN_R |= 0x0F;
  GPIO_PORTD_IS_R &= ~0x0F;
  GPIO_PORTD_IBE_R &= ~0x0F;
	//TIMER0_CTL_R &= ~TIMER_CTL_TBEVENT_M;
  GPIO_PORTD_IEV_R |= 0xFF; // PC7 falling edge event
  GPIO_PORTD_ICR_R = 0x0F;
  GPIO_PORTD_IM_R |= 0x0F;
	NVIC_PRI0_R = (NVIC_PRI0_R&0x0FFFFFFF)|0x20000000; // bits 29-31
  NVIC_EN0_R |= NVIC_EN0_INT3;
}/*
bool isControlActivated(short ctrlKey){
	updateXAxis();
	if(HWREGBITW(&gFlags, ctrlKey) == 1) {
		return True;
	} return False;
}*/
/*
bool isControlActivated(short ctrlKey){
	if(controlStatus & 1<<ctrlKey == True) {
		return True;
	} return False;
}*/
void setControl(bool status, short ctrlKey) {
	HWREGBITW(&gFlags, ctrlKey) = status;
}
void setXYAvg(void) {
	avgX = currX;
	//avgY = currY;
}
void updateXAxis(void) {
	if(ADCStatus0 == 0) {
		return;
	}
	//MAY NEED CALCULATION
	currX = ADCValue0;//(15*currX+ADCValue0)/16;
	ADCStatus0 = 0;
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
}
/*
void updateYAxis(void) {
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
}*/
void GPIOPortD_Handler(void) {
	HWREGBITW(&gFlags, SELECT_DOWN) = 1;
	GPIO_PORTD_ICR_R = 0x0F;
}

