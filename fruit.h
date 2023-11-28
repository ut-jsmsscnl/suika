#ifndef FRUIT_H_INCLUDED
#define FRUIT_H_INCLUDED
#include <stdlib.h>
#include "vector.h"

typedef struct _Fruit {
    Vector x, v, j;
    double r, density, m;
    char c;
    struct _Fruit *prev, *next;
} Fruit;

Fruit *createFruit(double x, double y, double r, char c);
Vector getImpulse(Vector n, Vector v, double rm, double e, double mu, double vb);
void boundCollision(Fruit *f, Vector n, double e, double mu, double vb);
void fruitCollision(Fruit *f1, Fruit *f2, double e, double mu, double vb);

#endif
