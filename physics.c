#include "physics.h"

void applyGravity(Fruit *f) {
    while(f != NULL) {
        vecMultAddA(&(f->v), _gravity, _dt);
        f = f->prev;
    }
}

double getBiasVel(double pd) {
    if(pd < _pdm) return 0.;
    return _bias / _dt * (pd - _pdm);
}

void checkBoundCol(Fruit *f) {
    double pd[3];
    while(f != NULL) {
        pd[0] = f->x.y + f->r - _boundy;
        pd[1] = f->r - f->x.x;
        pd[2] = f->x.x + f->r - _boundx;
        for(int bi = 0; bi < 3; bi++) {
            if(pd[bi] > 0.) {
                double vb = getBiasVel(pd[bi]);
                Vector j = getImpulse(_boundn[bi], f->v, f->m, vb);
                vecMultAddA(&(f->v), j, 1 / f->m);
            }
        }
        f = f->prev;
    }
}

void checkFruitCol(Fruit *f, ColPair **col) {
    Fruit *f1 = f, *f2;
    double pd;
    while(f1 != NULL) {
        f2 = f1->prev;
        while(f2 != NULL) {
            pd = f1->r + f2->r - vecDist(f1->x, f2->x);
            if(pd > 0.) {
                Vector n = vecNormalize(vecSub(f1->x, f2->x));
                Vector v = vecSub(f1->v, f2->v);
                double rm = 1 / (1 / f1->m + 1 / f2->m);
                double vb = getBiasVel(pd);
                Vector j = getImpulse(n, v, rm, vb);
                vecMultAddA(&(f1->v), j, 1 / f1->m);
                vecMultAddA(&(f2->v), vecMinus(j), 1 / f2->m);
                if(f1->type == f2->type) addColPair(col, f1, f2);
            }
            f2 = f2->prev;
        }
        f1 = f1->prev;
    }
}

void applyVelocity(Fruit *f) {
    while(f != NULL) {
        vecMultAddA(&(f->x), f->v, _dt);
        f = f->prev;
    }
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
