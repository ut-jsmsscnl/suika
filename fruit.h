#ifndef FRUIT_H_INCLUDED
#define FRUIT_H_INCLUDED
#include <stdlib.h>
#include "vector.h"

typedef struct _Fruit {
    Vector x, v, j;
    double r, density, m;
    struct _Fruit *prev, *next;
} Fruit;

Fruit *createFruit(double x, double y, double r) {
    Fruit *f = (Fruit*)malloc(sizeof(Fruit));
    vecSet(&(f->x), x, y);
    vecSet(&(f->v), 0.5, 0.5);
    f->r = r;
    f->density = 1.;
    f->m = r * r * f->density;
    f->prev = f->next = NULL;
    return f;
}

#endif
