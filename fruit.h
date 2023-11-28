#ifndef FRUIT_H_INCLUDED
#define FRUIT_H_INCLUDED
#include <stdlib.h>
#include "consts.h"

typedef struct _Fruit {
    Vector x, xp, v, j;
    int type;
    double r, m;
    struct _Fruit *prev, *next;
} Fruit;

Fruit *createFruit(double x, double y, int type);

#endif
