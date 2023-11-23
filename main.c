#include <stdio.h>
#include <stdlib.h>

typedef struct _Vector {
    double x, y;
} Vector;

typedef struct _Fruit {
    Vector x;
    double r;
    struct _Fruit *prev, *next;
} Fruit;

typedef struct _World {
    double xran, yran;
    int width, height;
    Fruit *f;
} World;

double dist2(Vector a, Vector b) {
    return (a.x-b.x) * (a.x-b.x) + (a.y-b.y) * (a.y-b.y);
}

Fruit *createFruit(double x, double y, double r) {
    Fruit *f = (Fruit*)malloc(sizeof(Fruit));
    f->x.x = x;
    f->x.y = y;
    f->r = r;
    f->prev = f->next = NULL;
    return f;
}

World *createWorld(double xran, double yran) {
    World *world = (World*)malloc(sizeof(World));
    world->xran = xran;
    world->yran = yran;
    world->width = (int)(20 * 2.5333 * xran / yran);
    world->height = 20;
    world->f = NULL;
    return world;
}

void destroyWorld(World *world) {
    Fruit *f1 = world->f, *f2 = NULL;
    while(f1 != NULL) {
        f2 = f1;
        f1 = f1->prev;
        free(f2);
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
        if(dist2(x, f->x) < f->r * f->r) {
            return '*';
        }
        f = f->prev;
    }
    return ' ';
}

void display(World *world) {
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

int main(int argc, char **argv) {
    World *world = createWorld(2., 3.);
    addFruit(world, createFruit(1., 1.2, 0.4));
    addFruit(world, createFruit(0.2, 2.2, 0.2));
    display(world);
    destroyWorld(world);
    return 0;
}
