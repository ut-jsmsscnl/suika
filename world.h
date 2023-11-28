#ifndef WORLD_H_INCLUDED
#define WORLD_H_INCLUDED
#include <stdio.h>
#include <threads.h>
#include "fruit.h"

typedef struct _World {
    Fruit *f;
    int width, height;
    struct timespec delay;
} World;

World *createWorld();
void destroyWorld(World *world);
void addFruit(World *world, Fruit *newf);
void applyGravity(World *world);
double getBiasVel(World *world, double pd);
void checkBoundCol(World *world);
void checkFruitCol(World *world);
void applyImpulse(World *world);
char getPixel(World *world, int i, int j);
void display(World *world);
int checkStopped(World *world);
void run(World *world);

#endif
