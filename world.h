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

void applyGravity(World *world) {
    Fruit *f = world->f;
    while(f != NULL) {
        vecMultAddA(&(f->v), world->gravity, world->dt);
        f = f->prev;
    }
}

void checkBoundCol(World *world) {
    Fruit *f = world->f;
    while(f != NULL) {
        f->j = (Vector){0., 0.};
        if(f->x.y + f->r > world->ymax) {
            boundCollision(f, (Vector){0., -1.}, world->e, world->mu);
        }
        if(f->x.x - f->r < 0.) {
            boundCollision(f, (Vector){1., 0.}, world->e, world->mu);
        }
        if(f->x.x + f->r > world->xmax) {
            boundCollision(f, (Vector){-1., 0.}, world->e, world->mu);
        }
        f = f->prev;
    }
}

void checkFruitCol(World *world) {
    Fruit *f1 = world->f, *f2;
    while(f1 != NULL) {
        f2 = f1->prev;
        while(f2 != NULL) {
            if(vecDistCloserThan(f1->x, f2->x, f1->r + f2->r)) {
                fruitCollision(f1, f2, world->e, world->mu);
            }
            f2 = f2->prev;
        }
        f1 = f1->prev;
    }
}

void applyImpulse(World *world) {
    Fruit *f = world->f;
    while(f != NULL) {
        vecMultAddA(&(f->v), f->j, 1 / f->m);
        vecMultAddA(&(f->x), f->v, world->dt);
        f = f->prev;
    }
}

char getPixel(World *world, int i, int j) {
    Vector x = {(j + .5) * world->xmax / world->width,
                (i + .5) * world->ymax / world->height};
    Fruit *f = world->f;
    while(f != NULL) {
        if(vecDistCloserThan(x, f->x, f->r)) {
            return f->c;
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
        applyGravity(world);
        checkBoundCol(world);
        checkFruitCol(world);
        applyImpulse(world);
        if(ti % world->subframe == 0) {
            display(world);
            printf("frame = %d\n", ti / world->subframe);
            thrd_sleep(&(world->delay), NULL);
        }
    }
}

#endif
