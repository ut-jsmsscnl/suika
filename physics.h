#ifndef PHYSICS_H_INCLUDED
#define PHYSICS_H_INCLUDED
#include "fruit.h"

void applyGravity(Fruit *f);
double getBiasVel(double pd);
void checkBoundCol(Fruit *f);
void checkFruitCol(Fruit *f, ColPair **col);
void applyVelocity(Fruit *f);
double getNormalImpulse(Vector n, Vector v, double mr, double vb);
double getTangentImpulse(Vector t, Vector v, double mr, double jn);

#endif
