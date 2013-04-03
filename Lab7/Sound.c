#include "Sound.h"
#include "SysTickInts.h"

char waveform[TABLE_SIZE] = {0};
volatile int sampleIndex = 0;
int tempo = 120;

void Sound_Init() {
	//Global Variables
	int i = 0;
	for(; i<TABLE_SIZE; i++) {
		waveform[i] = 4.0*sin(TAO*i/TABLE_SIZE)+4.0;
	}	
}

void Sound_Play(unsigned short freq) {
	double period = 1/(TABLE_SIZE*freq);
	sampleIndex = 0;
	Set_SysTick_Period(period);
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
