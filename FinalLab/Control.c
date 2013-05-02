#include "Control.h"

int controlStatus = 0;
int avgX=0, currX=0;
int avgY=0, currY=0;
short currSelectIndex = 0;

//SELECT BUTTON
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
}
void setXYAvg(void) {
	avgX = currX;
	avgY = 0x256;//currY;
}
//
void updateXAxis(void) {
	if(ADCStatus0 == 0) { return; }
	currX = ((X_SAMPLES-1)*currX+ADCValue0)/X_SAMPLES;
	ADCStatus0 = 0;
	//X axis
/*
	if(currX < avgX-ANALOG_THRESHOLD) {
		HWREGBITW(&gFlags, ANALOG_LEFT) = True;
		HWREGBITW(&gFlags, ANALOG_RIGHT) = False;
	} else if(avgX+ANALOG_THRESHOLD < currX) {
		HWREGBITW(&gFlags, ANALOG_LEFT) = False;
		HWREGBITW(&gFlags, ANALOG_RIGHT) = True;
	} else {
*/		HWREGBITW(&gFlags, ANALOG_LEFT) = False;
		HWREGBITW(&gFlags, ANALOG_RIGHT) = False;
	//}
}
void updateYAxis(void) {
	if(ADCStatus1 == 0) { return; }
	currY = ADCValue1;//((Y_SAMPLES-1)*currY+ADCValue1)/Y_SAMPLES;
	ADCStatus1 == 0;
	//Y axis
	if(currY < avgY-ANALOG_THRESHOLD) {
		HWREGBITW(&gFlags, ANALOG_UP) = False;
		HWREGBITW(&gFlags, ANALOG_DOWN) = True;
	} else if(avgY+ANALOG_THRESHOLD < currY) {
		HWREGBITW(&gFlags, ANALOG_UP) = True;
		HWREGBITW(&gFlags, ANALOG_DOWN) = False;
	} else {
		HWREGBITW(&gFlags, ANALOG_UP) = False;
		HWREGBITW(&gFlags, ANALOG_DOWN) = False;
	}
}
void GPIOPortD_Handler(void) {
	HWREGBITW(&gFlags, SELECT_DOWN) = 1;
	GPIO_PORTD_ICR_R = 0x0F;
}

