#include "ADC.h"
#include "hw_types.h"
#include "globals.h"
#include "lm3s1968.h"
#include "Delay.h"

#define ANALOG_THRESHOLD		200
#define X_SAMPLES						16

void portD_Init(void);
void GPIOPortG_Handler(void);
bool isControlActivated(short);
void setControl(bool, short);
void setXYAvg(void);
void updateXAxis(void);
void updateControls(void);


