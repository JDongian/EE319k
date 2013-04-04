#include "Sound.h"
#include "systick.h"

unsigned int waveform[TABLE_SIZE];
volatile int sampleIndex = 0;
int tempo = 180;

void Sound_Init() {
		//Global Variables
	int i = 0;
	for(; i<TABLE_SIZE; i++) {
		waveform[i] = (int)(7.0*sin(TAO*i/TABLE_SIZE)+7.0);
	}
}

void Sound_Play(unsigned short freq) {
	unsigned long period = SYS_TIME_CONST/(TABLE_SIZE*freq);
	sampleIndex = 0;
	SysTickPeriodSet(period);
}

void Sound_Play_Note(note n) {
	double i;
	if (n.frequency == 0) { Sound_Play(Off);
	} else { Sound_Play(n.frequency); }
	for (i = 0.0; i < n.time*200000/tempo; i++) {}
	//Sound_Play(Off);
	//for (i = 0.0; i < 10; i++) {}
}

void Sound_Play_Song(note song[]) {
	int i = 0;
	for (; song[i].time != 0; ++i) {
			Sound_Play_Note(song[i]);
	}
}

void Sound_Song(void) {
	note GreenHills[] = {
		{C5, quaver}, {A4, crotchet}, {C5, quaver}, 
		{B4, crotchet}, {C5, quaver}, {B4, crotchet}, {G4, minim+quaver}, 
		{A4, quaver}, {E5, quaver}, {D5, crotchet}, {C5, quaver},
		{B4, crotchet}, {C5, quaver}, {B4, crotchet}, {G4, minim+crotchet+quaver},
		
		{C5, quaver}, {A4, crotchet}, {C5, quaver}, 
		{B4, crotchet}, {C5, quaver}, {B4, crotchet}, {G4, minim+quaver}, 		
		{A4, crotchet}, {F4, crotchet}, {A4, quaver},
		{G4, crotchet}, {A4, quaver}, {G4, crotchet},	{C4, minim+crotchet},
		{C5, quaver}, {A4, crotchet}, {C5, quaver}, 
		{B4, crotchet}, {C5, quaver}, {B4, crotchet}, {G4, minim+quaver}, 
		{A4, quaver}, {E5, quaver}, {D5, crotchet}, {C5, quaver},
		{B4, crotchet}, {C5, quaver}, {B4, crotchet}, {G4, minim+crotchet+quaver},
		
		{C5, quaver}, {A4, crotchet}, {C5, quaver}, 
		{B4, crotchet}, {C5, quaver}, {B4, crotchet}, {G4, minim+quaver}, 		
		{A4, crotchet}, {F4, crotchet}, {A4, quaver},
		{G4, crotchet}, {A4, quaver}, {G4, crotchet},	{C4, minim+crotchet},
		{A4, 0}
	};
		note MaryHadALittleLamb[] = {
		{E4, crotchet}, {D4, crotchet}, {C4, crotchet}, {D4, crotchet},
		{E4, crotchet}, {E4, crotchet}, {E4, minim},
		{D4, crotchet}, {D4, crotchet}, {D4, minim},
		{E4, crotchet}, {E4, crotchet}, {E4, minim},
		{E4, crotchet}, {D4, crotchet}, {C4, crotchet}, {D4, crotchet},
		{E4, crotchet}, {E4, crotchet}, {E4, crotchet}, {C4, crotchet},
		{D4, crotchet}, {D4, crotchet}, {E4, crotchet}, {D4, crotchet},
		{C4, semibreve},
		{A4, 0}
	};
	note CScale[] = {
		{C4, crotchet}, {D4, crotchet}, {E4, crotchet}, {F4, crotchet},
		{G4, crotchet}, {A4, crotchet}, {B4, crotchet},
		{C5, semibreve}, {C4, semibreve},
		{A4, 0}
	};
	//	Sound_Play_Song(CScale);
	//Sound_Play_Song(MaryHadALittleLamb);
	Sound_Play_Song(GreenHills);
	Sound_Play(Off);
}

