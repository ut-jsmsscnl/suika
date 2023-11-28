#include "world.h"

int main(int argc, char **argv) {
    char ch = ' ';
    World *world = createWorld();
    display(world, 0);
    system("/bin/stty raw onlcr");
    while((ch = getchar()) != '.') {
        if(ch == 's') run(world);
        else if(ch == 'a') moveDropper(world, -1);
        else if(ch == 'd') moveDropper(world, 1);
        display(world, 0);
    }
    system("clear");
    system("/bin/stty cooked");
    destroyWorld(world);
    return 0;
}
