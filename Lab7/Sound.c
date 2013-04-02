#include <math.h>
#include <lm3s1968.h>
#define TAO 6.283185307179586
#define TABLE_SIZE 80000
void Sound_Init() 
{
	char table[TABLE_SIZE];
	int i;
	for(i = 0; i<TABLE_SIZE; i++)
	{
		table[i] = sin(TAO*i/TABLE_SIZE);
	}
}

void Sound_Play(unsigned char n)
{
	//play
}

