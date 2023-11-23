#include <stdio.h>
#include <stdlib.h>

typedef struct _Fruit {
    double x, y;
    double r;
} Fruit;

typedef struct _World {
    double x, y;
    int width, height;
    Fruit **f;
} World;

Fruit *createFruit(double x, double y, double r) {
    Fruit *f = (Fruit*)malloc(sizeof(Fruit));
    f->x = x;
    f->y = y;
    f->r = r;
    return f;
}

World *createWorld(double x, double y) {
    World *world = (World*)malloc(sizeof(World));
    world->x = x;
    world->y = y;
    world->width = (int)(20 * 2.5333 * x / y);
    world->height = 20;
    world->f = (Fruit**)malloc(100 * sizeof(Fruit*));
    for(int i = 0; i < 100; i++) world->f[i] = NULL;
    return world;
}

void destroyWorld(World *world) {
    free(world->f);
    free(world);
}

void addFruit(World *world, Fruit *newf) {
    for(int i = 0; i < 100; i++) {
        if(world->f[i] == NULL) world->f[i] = newf;
    }
}

char getpixel(World *world, int i, int j) {
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
    addFruit(world, createFruit(1., 1.2, 0.7));
    display(world);
    destroyWorld(world);
    return 0;
}
