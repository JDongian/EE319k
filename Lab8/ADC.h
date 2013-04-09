
//Variables
double zeroVoltage;
double maxVoltage;
double scaleFactor;

//Methods
void ADCInit(void);			//Sets some default values.
double getVoltage(void);		//Gets the raw signal across the pot.
void setZero(void);			//Sets the measure to 0.
void setMax(void);			//Sets the mesure to 2. (may be extraneous)
double getLength(int);			//Scales the input voltage to accurately represent the ruler.
