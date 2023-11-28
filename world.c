#include "world.h"

World *createWorld() {
    World *world = (World*)malloc(sizeof(World));
    world->f = NULL;
    world->width = (int)(20 * 2.5333 * _boundx / _boundy);
    world->height = 20;
    world->delay = (struct timespec){.tv_nsec = _nsec};
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
        vecMultAddA(&(f->v), _gravity, _dt);
        f = f->prev;
    }
}

double getBiasVel(World *world, double pd) {
    if(pd < _pdm) return 0;
    return _bias / _dt * (pd - _pdm);
}

void checkBoundCol(World *world) {
    Fruit *f = world->f;
    double pd[3], vb;
    while(f != NULL) {
        pd[0] = f->x.y + f->r - _boundy;
        pd[1] = f->r - f->x.x;
        pd[2] = f->x.x + f->r - _boundx;
        for(int bi = 0; bi < 3; bi++) {
            if(pd[bi] > 0.) {
                vb = getBiasVel(world, pd[bi]);
                boundCollision(f, _boundn[bi], vb);
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
                fruitCollision(f1, f2, vb);
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
        vecMultAddA(&(f->x), f->v, _dt);
        f = f->prev;
    }
}

char getPixel(World *world, int i, int j) {
    Vector x = {(j + .5) * _boundx / world->width,
                (i + .5) * _boundy / world->height};
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

int checkStopped(World *world) {
    Fruit *f = world->f;
    int stopped = 1;
    while(f != NULL) {
        if(vecDist(f->x, f->xp) > _dx) stopped = 0;
        f->xp = f->x;
        f = f->prev;
    }
    return stopped;
}

void run(World *world) {
    for(int frame = 0; frame < _maxf; frame++) {
        for(int sf = 0; sf < _subframe; sf++) {
            applyGravity(world);
            checkBoundCol(world);
            checkFruitCol(world);
            applyImpulse(world);
        }
        display(world);
        if(frame % _checkf == 0 && frame > 0) {
            if(checkStopped(world)) return;
        }
        thrd_sleep(&(world->delay), NULL);
    }
}
