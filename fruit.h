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

Vector getImpulse(Vector n, Vector v, double rm, double e, double mu) {
    Vector vn = vecMult(n, vecDot(n, v));
    Vector t = vecNormalize(vecSub(v, vn));
    double j = rm * (1+e) * vecNorm(vn);
    Vector jn = vecMult(n, j);
    Vector jt = vecMult(t, -j * mu);
    return vecAdd(jn, jt);
}

void boundCollision(Fruit *f, Vector n, double e, double mu) {
    if(vecDot(n, f->v) > 0.) return;
    Vector j = getImpulse(n, f->v, f->m, e, mu);
    vecAddA(&(f->j), j);
}

void fruitCollision(Fruit *f1, Fruit *f2, double e, double mu) {
    Vector n = vecNormalize(vecSub(f1->x, f2->x));
    Vector v = vecSub(f1->v, f2->v);
    if(vecDot(n, v) > 0.) return;
    Vector j = getImpulse(n, v, 1 / (1 / f1->m + 1 / f2->m), e, mu);
    vecAddA(&(f1->j), j);
    vecAddA(&(f2->j), vecMinus(j));
}

#endif
