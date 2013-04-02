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

void Sound_Play(unsigned char freq)
{
	int delay = 1/(TABLE_SIZE*freq);
	int i;
	while(i < TABLE_SIZE)
	{
		DAC_Out(table[i]);
		i++;
	}
	
	
}

