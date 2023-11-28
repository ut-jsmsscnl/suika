#include "fruit.h"

Fruit *createFruit(double x, double y, double r, char c) {
    Fruit *f = (Fruit*)malloc(sizeof(Fruit));
    f->x = f->xp = (Vector){x, y};
    f->v = f->j = (Vector){0., 0.};
    f->r = r;
    f->m = r * r;
    f->c = c;
    f->prev = f->next = NULL;
    return f;
}

Vector getImpulse(Vector n, Vector v, double rm, double vb) {
    double vn_ = vecDot(n, v) - vb;
    if(vn_ > 0.) return (Vector){0., 0.};
    Vector vn = vecMult(n, vn_);
    Vector vt = vecSub(v, vn);
    Vector t = vecNormalize(vt);
    double vt_ = vecNorm(vt);
    double j = -(1 + _e) * rm * vn_;
    Vector jn = vecMult(n, j);
    Vector jt;
    if(j * _mu > rm * vt_) {
        jt = vecMult(t, -rm * vt_);
    }
    else {
        jt = vecMult(t, -j * _mu);
    }
    return vecAdd(jn, jt);
}

void boundCollision(Fruit *f, Vector n, double vb) {
    Vector j = getImpulse(n, f->v, f->m, vb);
    vecAddA(&(f->j), j);
}

void fruitCollision(Fruit *f1, Fruit *f2, double vb) {
    Vector n = vecNormalize(vecSub(f1->x, f2->x));
    Vector v = vecSub(f1->v, f2->v);
    double rm = 1 / (1 / f1->m + 1 / f2->m);
    Vector j = getImpulse(n, v, rm, vb);
    vecAddA(&(f1->j), j);
    vecAddA(&(f2->j), vecMinus(j));
}
