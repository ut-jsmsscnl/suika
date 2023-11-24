#ifndef WORLD_H_INCLUDED
#define WORLD_H_INCLUDED
#include <stdio.h>
#include <threads.h>
#include "fruit.h"

typedef struct _World {
    Fruit *f;
    double xmax, ymax;
    int width, height;
    int fps, subframe;
    double dt;
    struct timespec delay;
    double e, mu;
    Vector gravity;
} World;

World *createWorld() {
    World *world = (World*)malloc(sizeof(World));
    world->xmax = 2.;
    world->ymax = 3.;
    world->width = (int)(20 * 2.5333 * world->xmax / world->ymax);
    world->height = 20;
    world->f = NULL;
    world->fps = 10;
    world->subframe = 5;
    world->dt = 1. / world->fps / world->subframe;
    world->delay = (struct timespec){.tv_nsec = 1E9 / world->fps};
    world->e = .2;
    world->mu = .1;
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

void simulate(World *world) {
    Fruit *f = world->f;
    while(f != NULL) {
        vecMultAddA(&(f->v), world->gravity, world->dt);
        f = f->prev;
    }
    f = world->f;
    while(f != NULL) {
        f->j = (Vector){0., 0.};
        if(f->x.y + f->r > world->ymax) {
            boundColision(f, (Vector){0., -1.}, world->e, world->mu);
        }
        if(f->x.x - f->r < 0.) {
            boundColision(f, (Vector){1., 0.}, world->e, world->mu);
        }
        if(f->x.x + f->r > world->xmax) {
            boundColision(f, (Vector){-1., 0.}, world->e, world->mu);
        }
        f = f->prev;
    }
    f = world->f;
    while(f != NULL) {
        vecMultAddA(&(f->v), f->j, 1 / f->m);
        vecMultAddA(&(f->x), f->v, world->dt);
        f = f->prev;
    }
}

Vector getWorldCoord(World *world, int i, int j) {
    Vector x;
    x.x = (j + .5) * world->xmax / world->width;
    x.y = (i + .5) * world->ymax / world->height;
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
        simulate(world);
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
