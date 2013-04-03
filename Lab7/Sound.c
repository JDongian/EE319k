#include "Sound.h"
#include "systick.h"

unsigned int waveform[TABLE_SIZE];
volatile int sampleIndex = 0;
int tempo = 120;

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
	for (i = 0.0; i < n.time*1000000/tempo; i++) {}
	Sound_Play(Off);
	for (i = 0.0; i < 10; i++) {}
}

void Sound_Play_Song(note song[]) {
	int i = 0;
	for (; song[i].time != 0; ++i) {
			Sound_Play_Note(song[i]);
	}
}

void Sound_Song(void) {
	note GreenHills[] = {
		{A5, semiquaver}, {F5, semiquaver}, {A5, semiquaver}, {F5, semiquaver}, {B5, semiquaver}, {G5, semiquaver}, {B5, semiquaver}, {G5, semiquaver}, {C5, semiquaver}, {A5, semiquaver}, {C5, semiquaver}, {A5, semiquaver}, {D5, semiquaver}, {B5, semiquaver}, {D5, semiquaver}, {B5, semiquaver},
		{G4, crotchet+quaver}, {F4, crotchet+quaver}, {G4, crotchet+quaver},
		{F4, crotchet+quaver}, {G4, crotchet}, {F4, crotchet},
		{A4, crotchet+quaver}, {G4, crotchet+quaver}, {F4, crotchet+semibreve},
		{F4, crotchet+quaver}, {G4, crotchet+quaver}, {A4, quaver},
		{F4, crotchet+quaver}, {G4, crotchet+quaver}, {A4, quaver},
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
	Sound_Play_Song(MaryHadALittleLamb);
	Sound_Play_Song(GreenHills);
}

