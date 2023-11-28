#ifndef PHYSICS_H_INCLUDED
#define PHYSICS_H_INCLUDED
#include "fruit.h"

void applyGravity(Fruit *f);
double getBiasVel(double pd);
void checkBoundCol(Fruit *f);
void checkFruitCol(Fruit *f1);
void applyImpulse(Fruit *f);
Vector getImpulse(Vector n, Vector v, double rm, double vb);

#endif
