#include "world.h"

int main(int argc, char **argv) {
    char ch = ' ';
    World *world = createWorld();
    display(world);
    system("/bin/stty raw onlcr");
    while((ch = getchar()) != '.') {
        if(ch == 's') run(world);
        else if(ch == 'a') moveLeft(world);
        else if(ch == 'd') moveRight(world);
        display(world);
    }
    system("clear");
    system("/bin/stty cooked");
    destroyWorld(world);
    return 0;
}
