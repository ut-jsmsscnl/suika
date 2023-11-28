#ifndef FRUIT_H_INCLUDED
#define FRUIT_H_INCLUDED
#include <stdlib.h>
#include "consts.h"

typedef struct _Fruit {
    Vector x, v, j;
    double r, m;
    char c;
    struct _Fruit *prev, *next;
} Fruit;

Fruit *createFruit(double x, double y, double r, char c);
Vector getImpulse(Vector n, Vector v, double rm, double vb);
void boundCollision(Fruit *f, Vector n, double vb);
void fruitCollision(Fruit *f1, Fruit *f2, double vb);

#endif
