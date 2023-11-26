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

Vector getImpulse(Vector n, Vector v, double rm,
                  double e, double mu, double ve) {
    if(vecDot(n, v) > 0.) return (Vector){0., 0.};
    Vector vn = vecMult(n, vecDot(n, v));
    Vector vt = vecSub(v, vn);
    double vnn = vecNorm(vn);
    double vtn = vecNorm(vt);
    if(vnn < ve && vtn < mu * vnn) return vecMult(v, -2 * rm);
    Vector t = vecNormalize(vt);
    double j = (1+e) * rm * vnn;
    if(j * mu > rm * vtn) mu = rm * vtn / j;
    Vector jn = vecMult(n, j);
    Vector jt = vecMult(t, -j * mu);
    return vecAdd(jn, jt);
}

void boundCollision(Fruit *f, Vector n,
                    double e, double mu, double ve) {
    Vector j = getImpulse(n, f->v, f->m, e, mu, ve);
    vecAddA(&(f->j), j);
}

void fruitCollision(Fruit *f1, Fruit *f2,
                    double e, double mu, double ve) {
    Vector n = vecNormalize(vecSub(f1->x, f2->x));
    Vector v = vecSub(f1->v, f2->v);
    double rm = 1 / (1 / f1->m + 1 / f2->m);
    Vector j = getImpulse(n, v, rm, e, mu, ve);
    vecAddA(&(f1->j), j);
    vecAddA(&(f2->j), vecMinus(j));
}

#endif
