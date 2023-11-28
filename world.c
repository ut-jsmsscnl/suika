#include "world.h"

World *createWorld() {
    World *world = (World*)malloc(sizeof(World));
    world->f = NULL;
    world->col = NULL;
    resetDropper(&(world->dr));
    world->width = (int)(20 * 2.5333 * _boundx / _boundy);
    world->height = 20;
    world->delay = (struct timespec){.tv_nsec = 1E9 / _fps};
    srand(_seed);
    display(world, 0);
    return world;
}

void deleteWorld(World *world) {
    Fruit *f = world->f, *fp;
    while(f != NULL) {
        fp = f->prev;
        free(f);
        f = fp;
    }
    free(world);
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

int checkStopped(Fruit *f) {
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

int checkMerge(World *world) {
    ColPair *colp;
    int merged = 0;
    while(world->col != NULL) {
        if(world->col->f1->type == world->col->f2->type) {
            Fruit *f1 = world->col->f1;
            Fruit *f2 = world->col->f2;
            if(f1->type < _ftn - 1) {
                Vector x = vecMult(vecAdd(f1->x, f2->x), .5);
                Fruit *newf = createFruit(x.x, x.y, f1->type + 1);
                addFruit(&(world->f), newf);
            }
            deleteFruit(&(world->f), world->col->f1);
            deleteFruit(&(world->f), world->col->f2);
            merged = 1;
        }
        colp = world->col->prev;
        free(world->col);
        world->col = colp;
    }
    return merged;
}

void run(World *world) {
    addFruit(&(world->f), world->dr.f);
    world->dr.f = NULL;
    checkStopped(world->f);
    for(int frame = 0; frame < _maxf; frame++) {
        for(int sf = 0; sf < _subframe; sf++) {
            applyGravity(world->f);
            checkBoundCol(world->f);
            checkFruitCol(world->f, &(world->col));
            applyImpulse(world->f);
            if(checkMerge(world)) {
                frame = 0;
                checkStopped(world->f);
            };
        }
        display(world, 1);
        if(!(frame % _checkf) && frame > 0) {
            if(checkStopped(world->f)) break;
        }
        thrd_sleep(&(world->delay), NULL);
    }
    resetDropper(&(world->dr));
}
