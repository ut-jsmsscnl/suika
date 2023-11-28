#ifndef WORLD_H_INCLUDED
#define WORLD_H_INCLUDED
#include <stdio.h>
#include <threads.h>
#include "physics.h"
#include "dropper.h"

typedef struct _World {
    Fruit *f;
    ColPair *col;
    Dropper dr;
    int width, height;
    struct timespec delay;
} World;

World *createWorld();
void deleteWorld(World *world);
char getPixel(World *world, int i, int j);
void display(World *world, int running);
int checkStopped(Fruit *f);
void checkMerge(World *world);
void run(World *world);

#endif
