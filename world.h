#ifndef WORLD_H_INCLUDED
#define WORLD_H_INCLUDED
#include <stdio.h>
#include <threads.h>
#include "physics.h"
#include "dropper.h"

typedef struct _World {
    Fruit *f;
    Dropper dr;
    int width, height;
    struct timespec delay;
} World;

World *createWorld();
void destroyWorld(World *world);
void addFruit(World *world, Fruit *newf);
char getPixel(World *world, int i, int j);
void display(World *world, int running);
int checkStopped(World *world);
void run(World *world);

#endif
