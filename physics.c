#include "physics.h"

void applyGravity(Fruit *f) {
    while(f != NULL) {
        vecMultAddA(&(f->v), _gravity, _dt);
        f = f->prev;
    }
}

double getBiasVel(double pd) {
    if(pd < _pdth) return 0.;
    return _bias / _dt * (pd - _pdth);
}

void checkBoundCol(Fruit *f) {
    double pd[3];
    Vector n[3] = {(Vector){0., -1.}, (Vector){1., 0.}, (Vector){-1., 0.}};
    Vector t[3] = {(Vector){1., 0.}, (Vector){0., 1.}, (Vector){0., -1.}};
    while(f != NULL) {
        pd[0] = f->x.y + f->r - _boundy;
        pd[1] = f->r - f->x.x;
        pd[2] = f->x.x + f->r - _boundx;
        for(int bi = 0; bi < 3; bi++) {
            if(pd[bi] > 0.) {
                double vb = getBiasVel(pd[bi]);
                double jn = getNormalImpulse(n[bi], f->v, f->m, vb);
                double jt = getTangentImpulse(t[bi], f->v, f->m, jn);
                vecMultAddA(&(f->v), n[bi], jn / f->m);
                vecMultAddA(&(f->v), t[bi], jt / f->m);
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
                Vector t = vecCross(n, 1.);
                Vector v = vecSub(f1->v, f2->v);
                double mr = 1 / (1 / f1->m + 1 / f2->m);
                double vb = getBiasVel(pd);
                double jn = getNormalImpulse(n, v, mr, vb);
                double jt = getTangentImpulse(t, v, mr, jn);
                vecMultAddA(&(f1->v), n, jn / f1->m);
                vecMultAddA(&(f1->v), t, jt / f1->m);
                vecMultAddA(&(f2->v), n, -jn / f2->m);
                vecMultAddA(&(f2->v), t, -jt / f2->m);
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

double getNormalImpulse(Vector n, Vector v, double mr, double vb) {
    double vn = vecDot(n, v) - vb;
    if(vn > 0.) return 0.;
    return -(1 + _e) * mr * vn;
}

double getTangentImpulse(Vector t, Vector v, double mr, double jn) {
    double vt = vecDot(t, v);
    if(vt > 0.) {
        if(_mu * jn > mr * vt) return -mr * vt;
        return -_mu * jn;
    }
    if(_mu * jn > mr * -vt) return -mr * vt;
    return _mu * jn;
}
