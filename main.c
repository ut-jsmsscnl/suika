#include <stdio.h>
#include <stdlib.h>

typedef struct _Screen {
    int width, height;
    char **c;
} Screen;

typedef struct _World {
    double x, y;
    Screen *s;
} World;

Screen* createScreen(int width, int height) {
    Screen *s = (Screen*)malloc(sizeof(Screen));
    s->width = width;
    s->height = height;
    s->c = (char**)malloc(height * sizeof(char*));
    for(int i = 0; i < height; i++) {
        s->c[i] = (char*)malloc(width * sizeof(char));
        for(int j = 0; j < width; j++) {
            s->c[i][j] = ' ';
        }
    }
    return s;
}

World *createWorld(double x, double y) {
    World *world = (World*)malloc(sizeof(World));
    world->x = x;
    world->y = y;
    world->s = createScreen(20*2.5333*x/y, 20);
    return world;
}

void display(Screen *s) {
    for(int i = 0; i < s->height; i++) {
        putchar('|');
        for(int j = 0; j < s->width; j++) {
            putchar(s->c[i][j]);
        }
        putchar('|');
        puts("");
    }
    for(int j = 0; j < s->width + 2; j++) {
        putchar('-');
    }
    puts("");
}

int main(int argc, char **argv) {
    World *world = createWorld(2., 3.);
    display(world->s);
    return 0;
}
