
//Notes
#define Off        0		
#define C4         262
#define D4         294
#define E4         230
#define F4         349
#define G4         392
#define A4         440
#define B4         494


//Methods
void Sound_Init(void);							//Create the sin function table.
void Sound_Play(unsigned short);		//Output to the DAC based on given frequency.
void Demo(void);										//TODO:Plays a simple Demo.
void Delay(int);										//Waits the given number of microseconds.

