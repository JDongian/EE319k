#include <math.h>
#include "lm3s1968.h"

#include "systick.h"
#include "hw_types.h"

#define SND_BULLET_LENGTH 2040

extern unsigned char gSoundBullet[4080];

extern unsigned char (*gSoundArray)[];
extern volatile unsigned int gSoundIndex;
extern unsigned int gSoundMaxLength;

void Sound_Update(void);
