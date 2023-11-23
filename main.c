#include <stdio.h>
#include <stdlib.h>

typedef struct _Window {
    int width, height;
    char **c;
} Window;

Window* createWindow(int width, int height) {
    Window *w = (Window*)malloc(sizeof(Window));
    w->width = width;
    w->height = height;
    w->c = (char**)malloc(height * sizeof(char*));
    for(int i = 0; i < height; i++) {
        w->c[i] = (char*)malloc(width * sizeof(char));
        for(int j = 0; j < width; j++) {
            w->c[i][j] = ' ';
        }
    }
    return w;
}

void display(Window *w) {
    for(int i = 0; i < w->height; i++) {
        putchar('|');
        for(int j = 0; j < w->width; j++) {
            putchar(w->c[i][j]);
        }
        putchar('|');
        puts("");
    }
    for(int j = 0; j < w->width + 2; j++) {
        putchar('-');
    }
    puts("");
}

int main(int argc, char **argv) {
    Window *w = createWindow(30, 15);
    display(w);
    return 0;
}
