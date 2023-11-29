#ifndef FRUIT_H_INCLUDED
#define FRUIT_H_INCLUDED
#include "consts.h"

typedef struct _Fruit {
    Vector x, xp, v;
    int type;
    double r, m;
    struct _Fruit *prev, *next;
} Fruit;

typedef struct _ColPair {
    int active;
    Fruit *f1, *f2;
    struct _ColPair *prev, *next;
} ColPair;

Fruit *createFruit(Vector x, Vector v, int type);
void addFruit(Fruit **f, Fruit *newf);
void deleteFruit(Fruit **f, Fruit *delf);
void addColPair(ColPair **col, Fruit *f1, Fruit *f2);

#endif
