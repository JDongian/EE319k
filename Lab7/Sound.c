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
		table[i] = 7*sin(TAO*i/TABLE_SIZE);
	}
}

void Sound_Play(unsigned char n)
{
	int delay = 1/(TABLE_SIZE*n);
	int i;
	while(i < TABLE_SIZE)
	{
		DAC_Out(table[i]);
	}
	
	
}

