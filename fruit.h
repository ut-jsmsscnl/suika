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
    f->x = (Vector){x, y};
    f->v = (Vector){0.5, 0.5};
    f->r = r;
    f->density = 1.;
    f->m = r * r * f->density;
    f->prev = f->next = NULL;
    return f;
}

void applyGravity(Fruit *f, Vector gravity, double dt) {
    vecMultAdd(&(f->j), gravity, f->m * dt);
}

void checkBoundaryCol(Fruit *f, double x, double y, double e) {
    if(f->x.y + f->r > y && f->v.y > 0) {
        f->j.y = f->m * -(1 + e) * f->v.y;
    }
    if(f->x.x - f->r < 0 && f->v.x < 0 ||
       f->x.x + f->r > x && f->v.x > 0) {
        f->j.x = f->m * -(1 + e) * f->v.x;
    }
}

#endif
