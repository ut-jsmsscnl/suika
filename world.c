#include "world.h"

World *createWorld(int argc, char **argv) {
    World *world = (World*)malloc(sizeof(World));
    world->f = NULL;
    world->col = NULL;
    resetDropper(&(world->dr));
    parse(world, argc, argv);
    world->limiti = (int)(_limity * world->height / _boundy);
    world->score = world->gameOver = 0;
    world->delay = (struct timespec){.tv_nsec = 1E9 / _fps};
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

void parse(World *world, int argc, char **argv) {
    int twidth = _twidth - 2, theight = _theight - 3;
    double aspect = _aspect;
    if(argc > 1) theight = atoi(argv[1]) - 3;
    if(argc > 2) twidth = atoi(argv[2]) - 2;
    if(argc > 3) aspect = atoi(argv[3]);
    world->height = theight;
    world->width = (int)(world->height * _boundx / _boundy * aspect);
    if(world->width > twidth) {
        world->width = twidth;
        world->height = (int)(world->width * _boundy / _boundx / aspect);
    }
}

void render(World *world, int i, int j) {
    Vector x = {(j + .5) * _boundx / world->width,
                (i + .5) * _boundy / world->height};
    Fruit *f = world->dr.f;
    if(f != NULL) {
        if(vecDist2(x, f->x) < f->r * f->r) {
            printf("%s", _fcol[f->type]);
            putchar(_fch[f->type]);
            printf(_DEF);
            return;
        }
    }
    f = world->f;
    while(f != NULL) {
        if(vecDist2(x, f->x) < f->r * f->r) {
            printf("%s", _fcol[f->type]);
            putchar(_fch[f->type]);
            printf(_DEF);
            return;
        }
        f = f->prev;
    }
    if(i == world->limiti) putchar('X');
    else putchar(' ');
}

void display(World *world, int running) {
    system("clear");
    printf(_GREEN "SCORE : %d\r\n" _DEF, world->score);
    for(int i = 0; i < world->height; i++) {
        putchar('|');
        for(int j = 0; j < world->width; j++) render(world, i, j);
        printf("|\r\n");
    }
    putchar('|');
    for(int j = 0; j < world->width; j++) putchar('-');
    printf("|\r\n");
    if(world->gameOver) printf(_RED "GAME OVER > " _DEF);
    else if(!running) printf("> ");
}

void updatePrev(World *world) {
    world->stopped = 1;
    Fruit *f = world->f;
    while(f != NULL) {
        if(f->xp.x == NAN) world->stopped = 0;
        else if(vecDist(f->x, f->xp) > _xth) world->stopped = 0;
        else if(vecNorm(f->v) > _vth) world->stopped = 0;
        f->xp = f->x;
        f = f->prev;
    }
}

void merge(World *world) {
    world->merged = 0;
    ColPair *colp;
    while(world->col != NULL) {
        if(world->col->active) {
            Fruit *f1 = world->col->f1;
            Fruit *f2 = world->col->f2;
            int type = f1->type;
            ColPair *colp = world->col->prev;
            while(colp != NULL) {
                if(colp->f1 == f1 || colp->f2 == f1 ||
                   colp->f1 == f2 || colp->f2 == f2) {
                    colp->active = 0;
                }
                colp = colp->prev;
            }
            if(type < _ftn - 1) {
                Vector x = vecMult(vecAdd(f1->x, f2->x), .5);
                Vector v = vecMult(vecAdd(f1->v, f2->v), .5);
                Fruit *newf = createFruit(x, v, type + 1);
                addFruit(&(world->f), newf);
            }
            deleteFruit(&(world->f), world->col->f1);
            deleteFruit(&(world->f), world->col->f2);
            world->score += _fs[type];
            world->merged = 1;
        }
        colp = world->col->prev;
        free(world->col);
        world->col = colp;
    }
}

void checkGameOver(World *world) {
    world->gameOver = 0;
    Fruit *f = world->f;
    while(f != NULL) {
        if(f->x.y < _limity) {
            world->gameOver = 1;
            return;
        }
        f = f->prev;
    }
}

void run(World *world) {
    addFruit(&(world->f), world->dr.f);
    world->dr.f = NULL;
    updatePrev(world);
    for(int frame = 0; frame < _maxf; frame++) {
        for(int sf = 0; sf < _subframe; sf++) {
            applyGravity(world->f);
            checkBoundCol(world->f);
            checkFruitCol(world->f, &(world->col));
            applyVelocity(world->f);
            merge(world);
        }
        display(world, 1);
        if(world->merged) {
            world->merged = 0;
            frame = 0;
            updatePrev(world);
        };
        if(!(frame % _checkf) && frame > 0) {
            updatePrev(world);
            if(world->stopped) break;
        }
        thrd_sleep(&(world->delay), NULL);
    }
    checkGameOver(world);
    if(!world->gameOver) resetDropper(&(world->dr));
}
