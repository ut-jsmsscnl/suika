#include "world.h"

World *createWorld() {
    World *world = (World*)malloc(sizeof(World));
    world->f = NULL;
    resetDropper(&(world->dr));
    world->width = (int)(20 * 2.5333 * _boundx / _boundy);
    world->height = 20;
    world->delay = (struct timespec){.tv_nsec = 1E9 / _fps};
    srand(_seed);
    display(world, 0);
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

char getPixel(World *world, int i, int j) {
    Vector x = {(j + .5) * _boundx / world->width,
                (i + .5) * _boundy / world->height};
    Fruit *f = world->dr.f;
    if(f != NULL) {
        if(vecDist2(x, f->x) < f->r * f->r) return _fc[f->type];
    }
    f = world->f;
    while(f != NULL) {
        if(vecDist2(x, f->x) < f->r * f->r) return _fc[f->type];
        f = f->prev;
    }
    return ' ';
}

void display(World *world, int running) {
    system("clear");
    for(int i = 0; i < world->height; i++) {
        putchar('|');
        for(int j = 0; j < world->width; j++) {
            putchar(getPixel(world, i, j));
        }
        printf("|\r\n");
    }
    putchar('|');
    for(int j = 0; j < world->width; j++) {
        putchar('-');
    }
    printf("|\r\n");
    if(!running) printf("> ");
}

int checkStopped(World *world) {
    Fruit *f = world->f;
    int stopped = 1;
    while(f != NULL) {
        if(f->xp.x == NAN) stopped = 0;
        else if(vecDist(f->x, f->xp) > _xth) stopped = 0;
        else if(vecNorm(f->v) > _vth) stopped = 0;
        f->xp = f->x;
        f = f->prev;
    }
    return stopped;
}

void run(World *world) {
    addFruit(world, world->dr.f);
    world->dr.f = NULL;
    checkStopped(world);
    for(int frame = 0; frame < _maxf; frame++) {
        for(int sf = 0; sf < _subframe; sf++) {
            applyGravity(world->f);
            checkBoundCol(world->f);
            checkFruitCol(world->f);
            applyImpulse(world->f);
        }
        display(world, 1);
        if(!(frame % _checkf) && frame > 0) {
            if(checkStopped(world)) break;
        }
        thrd_sleep(&(world->delay), NULL);
    }
    resetDropper(&(world->dr));
}
