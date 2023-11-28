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

typedef struct _ColPair {
    int active;
    Fruit *f1, *f2;
    struct _ColPair *prev, *next;
} ColPair;

Fruit *createFruit(double x, double y, int type);
void addFruit(Fruit **f, Fruit *newf);
void deleteFruit(Fruit **f, Fruit *delf);
void addColPair(ColPair **col, Fruit *f1, Fruit *f2);

#endif
