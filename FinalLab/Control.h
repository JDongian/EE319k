#include "ADC.h"
#include "hw_types.h"
#include "globals.h"
#include "lm3s1968.h"
#include "Delay.h"

#define ANALOG_THRESHOLD		32
#define SELECT_SAMPLES			16

#define ANALOG_UP				0
#define ANALOG_DOWN			1
#define ANALOG_LEFT			2
#define ANALOG_RIGHT		3
#define SELECT					4


void portD_Init(void);
bool isControlActivated(short);
void setControl(bool, short);
void setXYAvg(void);
void updateControls(void);


