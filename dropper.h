#ifndef DROPPER_H_INCLUDED
#define DROPPER_H_INCLUDED
#include "fruit.h"

typedef struct _Dropper {
    Fruit *f;
    int x;
} Dropper;

void resetDropper(Dropper *dr);
void moveDropper(Dropper *dr, int dir);

#endif
