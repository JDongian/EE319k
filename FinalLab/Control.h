#include "ADC.h"
#include "hw_types.h"
#include "globals.h"
#include "lm3s1968.h"
#include "Delay.h"

#define ANALOG_THRESHOLD		32
#define SELECT_SAMPLES			16

#define SELECT					4


void portD_Init(void);
void GPIOPortG_Handler(void);
bool isControlActivated(short);
void setControl(bool, short);
void setXYAvg(void);
void updateControls(void);


