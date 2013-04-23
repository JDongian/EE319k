#include "Sound.h"

unsigned int waveform[TABLE_SIZE];
volatile int sampleIndex = 0;
int tempo = 180;
bool play = False;

void Sound_Init() {
		//Global Variables
	int i = 0;
	for(; i<TABLE_SIZE; i++) {
		waveform[i] = (int)(7.0*sin(TAO*i/TABLE_SIZE)+7.49);
	}
}

void Sound_Play(unsigned short freq) {
	if (freq == 0) {
		play = False;
	} else {
		unsigned long period = SYS_TIME_CONST/(TABLE_SIZE*freq);
		sampleIndex = 0;
		SysTickPeriodSet(period);
		play = True;
	}
}

void Sound_Play_Note(note n) {
	double i;
	if (n.frequency == 0) { Sound_Play(Off);
	} else { Sound_Play(n.frequency); }
	for (i = 0.0; i < n.time*200000/tempo; i++) {}
}

void Sound_Play_Song(note song[]) {
	int i = 0;
	for (; song[i].time != 0; i++) {
			Sound_Play_Note(song[i]);
	}
}

void Sound_Song(void) {/*
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
	};*/
	note GuilesTheme[] = {
		{Ds4, quaver}, {Ds4, semiquaver}, {D4, semiquaver}, {Off, semiquaver}, {D4, semiquaver}, {Ds4, quaver+crotchet}, {D4, quaver},
		{Ds4, quaver}, {Ds4, semiquaver}, {D4, semiquaver}, {Off, semiquaver}, {D4, semiquaver}, {Ds4, quaver+crotchet}, {D4, quaver},
		{Ds4, semiquaver}, {D4, quaver}, {Ds4, semiquaver}, {Off, semiquaver}, {D4, quaver}, {F4, semiquaver}, {Off, semiquaver}, {F4, semiquaver}, {Ds4, quaver}, {D4, quaver}, {As3, quaver},
		{Ds4, quaver}, {Ds4, semiquaver}, {D4, semiquaver}, {Off, semiquaver}, {D4, semiquaver}, {Ds4, quaver+crotchet}, {D4, quaver},
		{Ds4, quaver}, {Ds4, semiquaver}, {D4, semiquaver}, {Off, semiquaver}, {D4, semiquaver}, {Ds4, quaver+crotchet}, {D4, quaver},
		{Ds4, semiquaver}, {D4, quaver}, {Ds4, semiquaver}, {Off, semiquaver}, {D4, quaver}, {F4, semiquaver}, {Off, semiquaver}, {F4, semiquaver}, {Ds4, quaver}, {D4, quaver}, {As3, quaver},
		{C3, minim+quaver}, {D3, quaver}, {Ds3, semiquaver}, {F3, quaver+semiquaver},
		{G3, quaver+semiquaver}, {G3, semiquaver}, {F3, quaver}, {As3, quaver+quaver}, {Gs3, quaver}, {G3, semiquaver}, {Gs3, quaver+semiquaver},
		{D3, quaver+semiquaver}, {Ds3, semiquaver+quaver}, {F3, quaver}, {Off, quaver}, {As2, quaver}, {D3, quaver}, {F3, quaver},
		{Gs3, quaver+semiquaver}, {As3, semiquaver+quaver}, {G3, quaver}, {Off, quaver}, {G3, quaver}, {F3, quaver}, {D3, quaver},
		{C3, semibreve},
		{A4, 0}
	};
	Sound_Play_Song(GuilesTheme);
	Sound_Play(Off);
}

