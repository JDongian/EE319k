#include "Delay.h"

void delay(unsigned int time){
	int i = 0;
	for (;i<time*timeScale;i++){}
}

void doNothing(){
	int i=1;
	i++;
	i--;
}
