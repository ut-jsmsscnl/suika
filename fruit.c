#include "fruit.h"

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
                  double e, double mu, double vb) {
    double vn = vecDot(n, v) - vb;
    if(vn > 0.) return (Vector){0., 0.};
    Vector t = vecSub(v, vecMult(n, vn));
    double vt = vecNorm(t);
    double j = -(1+e) * rm * vn;
    if(j * mu > rm * vt) mu = rm * vt / j;
    Vector jn = vecMult(n, j);
    Vector jt = vecMult(vecNormalize(t), -j * mu);
    return vecAdd(jn, jt);
}

void boundCollision(Fruit *f, Vector n,
                    double e, double mu, double vb) {
    Vector j = getImpulse(n, f->v, f->m, e, mu, vb);
    vecAddA(&(f->j), j);
}

void fruitCollision(Fruit *f1, Fruit *f2,
                    double e, double mu, double vb) {
    Vector n = vecNormalize(vecSub(f1->x, f2->x));
    Vector v = vecSub(f1->v, f2->v);
    double rm = 1 / (1 / f1->m + 1 / f2->m);
    Vector j = getImpulse(n, v, rm, e, mu, vb);
    vecAddA(&(f1->j), j);
    vecAddA(&(f2->j), vecMinus(j));
}
