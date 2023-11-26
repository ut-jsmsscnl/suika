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

Fruit *createFruit(double x, double y, double r, char c) {
    Fruit *f = (Fruit*)malloc(sizeof(Fruit));
    f->x = (Vector){x, y};
    f->v = (Vector){0., 0.};
    f->j = (Vector){0., 0.};
    f->r = r;
    f->density = 1.;
    f->m = r * r * f->density;
    f->c = c;
    f->prev = f->next = NULL;
    return f;
}

void boundColision(Fruit *f, Vector n, double e, double mu) {
    if(vecDot(n, f->v) > 0.) return;
    Vector vn = vecMult(n, vecDot(n, f->v));
    Vector t = vecNormalize(vecSub(f->v, vn));
    double j = f->m * (1 + e) * vecNorm(vn);
    Vector jn = vecMult(n, j);
    Vector jt = vecMult(t, -j * mu);
    vecAddA(&(f->j), jn);
    vecAddA(&(f->j), jt);
}

#endif
