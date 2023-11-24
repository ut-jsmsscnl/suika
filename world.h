#ifndef WORLD_H_INCLUDED
#define WORLD_H_INCLUDED
#include <stdio.h>
#include <threads.h>
#include "fruit.h"

typedef struct _World {
    Fruit *f;
    double x, y;
    int width, height;
    int fps, subframe;
    double dt;
    struct timespec delay;
    double e;
    Vector gravity;
} World;

World *createWorld() {
    World *world = (World*)malloc(sizeof(World));
    world->x = 2.;
    world->y = 3.;
    world->width = (int)(20 * 2.5333 * world->x / world->y);
    world->height = 20;
    world->f = NULL;
    world->fps = 10;
    world->subframe = 5;
    world->dt = 1. / world->fps / world->subframe;
    world->delay = (struct timespec){.tv_nsec = 1E9 / world->fps};
    world->e = .2;
    world->gravity = (Vector){0., 1.};
    return world;
}

void destroyWorld(World *world) {
    Fruit *f = world->f, *fp = NULL;
    while(f != NULL) {
        fp = f->prev;
        free(f);
        f = fp;
    }
    free(world);
}

void addFruit(World *world, Fruit *newf) {
    if(world->f != NULL) {
        world->f->next = newf;
        newf->prev = world->f;
    }
    world->f = newf;
}

void calcImpulse(World *world) {
    Fruit *f = world->f;
    while(f != NULL) {
        f->j = (Vector){0., 0.};
        applyGravity(f, world->gravity, world->dt);
        checkBoundaryCol(f, world->x, world->y, world->e);
        f = f->prev;
    }
}

void applyImpulse(World *world) {
    Fruit *f = world->f;
    while(f != NULL) {
        vecMultAdd(&(f->v), f->j, 1 / f->m);
        vecMultAdd(&(f->x), f->v, world->dt);
        f = f->prev;
    }
}

Vector getWorldCoord(World *world, int i, int j) {
    Vector x;
    x.x = (j + .5) * world->x / world->width;
    x.y = (i + .5) * world->y / world->height;
    return x;
}

char getPixel(World *world, int i, int j) {
    Vector x = getWorldCoord(world, i, j);
    Fruit *f = world->f;
    while(f != NULL) {
        if(vecDist2(x, f->x) < f->r * f->r) {
            return '*';
        }
        f = f->prev;
    }
    return ' ';
}

void display(World *world) {
    system("clear");
    for(int i = 0; i < world->height; i++) {
        putchar('|');
        for(int j = 0; j < world->width; j++) {
            putchar(getPixel(world, i, j));
        }
        puts("|");
    }
    putchar('|');
    for(int j = 0; j < world->width; j++) {
        putchar('-');
    }
    puts("|");
}

void run(World *world) {
    Fruit *f;
    for(int ti = 0; ti < 100 * world->subframe; ti++) {
        calcImpulse(world);
        applyImpulse(world);
        if(ti % world->subframe == 0) {
            display(world);
            printf("frame = %d\n", ti / world->subframe);
            printf("x %lf\t%lf\n", world->f->x.x, world->f->x.y);
            printf("v %lf\t%lf\n", world->f->v.x, world->f->v.y);
            printf("j %lf\t%lf\n", world->f->j.x, world->f->j.y);
            thrd_sleep(&(world->delay), NULL);
        }
    }
}

#endif
