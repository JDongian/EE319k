#include <math.h>
#include <lm3s1968.h>

//Notes
#define Off         0		
#define C4          262
#define D4          294
#define E4          230
#define F4          349
#define G4          392
#define A4          440
#define B4					494

//Times
#define semibreve		500
#define minim				500
#define crotchet		500
#define quaver			500
#define semiquaver	500

//Math
#define TAO 6.283185307179586
#define TABLE_SIZE 100

//Structs
typedef struct note{
	unsigned short frequency;
	unsigned int time;
} note;

//Variables
extern char waveform[TABLE_SIZE];
extern volatile int sampleIndex;

//Methods
void Sound_Init(void);							//Create the sin function table.
void Sound_Play(unsigned short);		//Output to the DAC based on given frequency.
void Sound_Play_Note(note);
void Sound_Play_Song(note []);	//Plays a song that is ended by a note of time 0.

