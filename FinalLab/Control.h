#include "ADC.h"
#include "hw_types.h"
#include "globals.h"
#include "lm3s1968.h"
#include "Delay.h"

#define ANALOG_THRESHOLD		0x100
#define X_SAMPLES						2
#define Y_SAMPLES						2

void portD_Init(void);
void GPIOPortG_Handler(void);
bool isControlActivated(short);
void setXYAvg(void);
void updateXAxis(void);
void updateYAxis(void);
void updateControls(void);


