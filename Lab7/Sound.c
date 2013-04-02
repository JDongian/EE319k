
#include "Sound.h"
#include "DAC.h"
#include <math.h>
#include <lm3s1968.h>
#define TAO 6.283185307179586
#define TABLE_SIZE 100

char table[TABLE_SIZE];
void Sound_Init() 
{
	int i;
	for(i = 0; i<TABLE_SIZE; i++)
	{
		table[i] = 4.0*sin(TAO*i/TABLE_SIZE)+4.0;
	}
}

void Sound_Play(unsigned short freq)
{
	int delay = 1/(TABLE_SIZE*freq);
	int i;
	if (freq == 0){
		DAC_Out(0);
		return;
	}
	while(i < TABLE_SIZE)
	{
		DAC_Out(table[i]);
		//Delay
		i++;
	}
}

void Demo(){
	Sound_Play(E4);
	Sound_Play(Off);
	Sound_Play(D4);
	Sound_Play(Off);
	Sound_Play(C4);
	Sound_Play(Off);
	Sound_Play(D4);
	Sound_Play(D4);
}

void Delay(int microseconds){
	return;
}
