#include <stdio.h>
#include <stdlib.h>
#include <threads.h>

typedef struct _Vector {
    double x, y;
} Vector;

typedef struct _Fruit {
    Vector x, v;
    double r;
    struct _Fruit *prev, *next;
} Fruit;

typedef struct _World {
    double xran, yran;
    int width, height;
    Fruit *f;
    double dt, e;
    Vector gravity;
} World;

void vecMultAdd(Vector *a, Vector b, double k) {
    a->x += b.x * k;
    a->y += b.y * k;
}

double vecDist2(Vector a, Vector b) {
    double dx = a.x - b.x;
    double dy = a.y - b.y;
    return dx * dx + dy * dy;
}

Fruit *createFruit(double x, double y, double r) {
    Fruit *f = (Fruit*)malloc(sizeof(Fruit));
    f->x.x = x;
    f->x.y = y;
    f->v.x = 0.5;
    f->v.y = 0.;
    f->r = r;
    f->prev = NULL;
    f->next = NULL;
    return f;
}

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

void applyGravity(World *world) {
    Fruit *f = world->f;
    while(f != NULL) {
        vecMultAdd(&(f->v), world->gravity, world->dt);
        f = f->prev;
    }
}

void applyCollision(World *world) {
    Fruit *f = world->f;
    while(f != NULL) {
        if(f->x.y + f->r > world->yran && f->v.y > 0) {
            f->v.y *= -world->e;
        }
        if(f->x.x - f->r < 0 && f->v.x < 0 ||
           f->x.x + f->r > world->xran && f->v.x > 0) {
            f->v.x *= -world->e;
        }
        f = f->prev;
    }
}

void move(World *world) {
    Fruit *f = world->f;
    while(f != NULL) {
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
    for(int ti = 0; ti < 50; ti++) {
        applyGravity(world);
        applyCollision(world);
        move(world);
        display(world);
        printf("ti = %d\n", ti);
        thrd_sleep(&delay, NULL);
    }
}

int main(int argc, char **argv) {
    World *world = createWorld();
    addFruit(world, createFruit(1., 1.2, 0.4));
    addFruit(world, createFruit(0.2, 2.2, 0.2));
    run(world);
    destroyWorld(world);
    return 0;
}
