#include <stdio.h>
#include <stdlib.h>
#include <threads.h>
#include "vector.h"
#include "fruit.h"

typedef struct _World {
    double xran, yran;
    int width, height;
    Fruit *f;
    double dt;
    Vector gravity;
    double e;
} World;

World *createWorld() {
    World *world = (World*)malloc(sizeof(World));
    world->xran = 2.;
    world->yran = 3.;
    world->width = (int)(20 * 2.5333 * 2. / 3.);
    world->height = 20;
    world->f = NULL;
    world->dt = 0.1;
    world->e = 0.3;
    world->gravity.x = 0.;
    world->gravity.y = 0.8;
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
        f->j.x = f->m * world->gravity.x * world->dt;
        f->j.y = f->m * world->gravity.y * world->dt;
        if(f->x.y + f->r > world->yran) {
            f->j.y = f->m * -(1 + world->e) * f->v.y;
        }
        if(f->x.x - f->r < 0 || f->x.x + f->r > world->xran) {
            f->j.x = f->m * -(1 + world->e) * f->v.x;
        }
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
    x.x = (j + .5) * world->xran / world->width;
    x.y = (i + .5) * world->yran / world->height;
    return x;
}

char getpixel(World *world, int i, int j) {
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
            putchar(getpixel(world, i, j));
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
    struct timespec delay = {.tv_nsec = world->dt * 1E9};
    Fruit *f;
    for(int ti = 0; ti < 100; ti++) {
        calcImpulse(world);
        applyImpulse(world);
        display(world);
        printf("ti = %d\n", ti);
        printf("y  %lf\n", world->f->x.y);
        printf("vy %lf\n", world->f->v.y);
        printf("jy %lf\n", world->f->j.y);
        thrd_sleep(&delay, NULL);
    }
}

int main(int argc, char **argv) {
    World *world = createWorld();
    addFruit(world, createFruit(1., 1.6, 0.4));
    //addFruit(world, createFruit(0.2, 2.2, 0.2));
    run(world);
    destroyWorld(world);
    return 0;
}
