#ifndef FRUIT_H_INCLUDED
#define FRUIT_H_INCLUDED
#include "vector.h"

typedef struct _Fruit {
    Vector x, v, j;
    double r, density, m;
    struct _Fruit *prev, *next;
} Fruit;

Fruit *createFruit(double x, double y, double r) {
    Fruit *f = (Fruit*)malloc(sizeof(Fruit));
    f->x.x = x;
    f->x.y = y;
    f->v.x = 0.5;
    f->v.y = 0.5;
    f->r = r;
    f->density = 1.;
    f->m = r * r * f->density;
    f->prev = NULL;
    f->next = NULL;
    return f;
}

#endif
