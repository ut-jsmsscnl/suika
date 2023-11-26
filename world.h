#ifndef WORLD_H_INCLUDED
#define WORLD_H_INCLUDED
#include <stdio.h>
#include <threads.h>
#include "fruit.h"

typedef struct _World {
    Fruit *f;
    double xmax, ymax;
    int width, height;
    Vector gravity;
    double e, mu, bias, pdm;
    int fps, subframe;
    double dt;
    struct timespec delay;
    //double ec, ve;
} World;

World *createWorld() {
    World *world = (World*)malloc(sizeof(World));
    world->f = NULL;
    world->xmax = 2.;
    world->ymax = 3.;
    world->width = (int)(20 * 2.5333 * world->xmax / world->ymax);
    world->height = 20;
    world->gravity = (Vector){0., 1.};
    world->e = .2;
    world->mu = .1;
    world->bias = 0.2;
    world->pdm = 0.01;
    world->fps = 10;
    world->subframe = 5;
    world->dt = 1. / world->fps / world->subframe;
    world->delay = (struct timespec){.tv_nsec = 1E9 / world->fps};
    //world->ec = 1E-3;
    //world->ve = sqrt(2 * vecNorm(world->gravity) * world->ec);
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
        f->j = (Vector){0., 0.};
        vecMultAddA(&(f->v), world->gravity, world->dt);
        f = f->prev;
    }
}

double getBiasVel(World *world, double pd) {
    if(pd < world->pdm) return 0;
    return world->bias / world->dt * (pd - world->pdm);
}

void checkBoundCol(World *world) {
    Fruit *f = world->f;
    double pd[3], vb;
    Vector n[3] = {(Vector){0., -1.}, (Vector){1., 0.}, (Vector){-1., 0.}};
    while(f != NULL) {
        pd[0] = f->x.y + f->r - world->ymax;
        pd[1] = f->r - f->x.x;
        pd[2] = f->x.x + f->r - world->xmax;
        for(int i = 0; i < 3; i++) {
            if(pd[i] > 0.) {
                vb = getBiasVel(world, pd[i]);
                boundCollision(f, n[i], world->e, world->mu, vb);
            }
        }
        f = f->prev;
    }
}

void checkFruitCol(World *world) {
    Fruit *f1 = world->f, *f2;
    double pd, vb;
    while(f1 != NULL) {
        f2 = f1->prev;
        while(f2 != NULL) {
            pd = f1->r + f2->r - vecDist(f1->x, f2->x);
            if(pd > 0.) {
                vb = getBiasVel(world, pd);
                fruitCollision(f1, f2, world->e, world->mu, vb);
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
        if(vecDist2(x, f->x) < f->r * f->r) {
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
    for(int i = 0; i < 1000 * world->subframe; i++) {
        applyGravity(world);
        checkBoundCol(world);
        checkFruitCol(world);
        applyImpulse(world);
        if(i % world->subframe == 0) {
            display(world);
            printf("frame = %d\n", i / world->subframe);
            Fruit *f2 = world->f, *f1 = f2->prev;
            printf("x1 %lf %lf x2 %lf %lf\n", f1->x.x, f1->x.y, f2->x.x, f2->x.y);
            printf("v1 %lf %lf v2 %lf %lf\n", f1->v.x, f1->v.y, f2->v.x, f2->v.y);
            printf("j1 %lf %lf j2 %lf %lf\n", f1->j.x, f1->j.y, f2->j.x, f2->j.y);
            thrd_sleep(&(world->delay), NULL);
        }
    }
}

#endif
