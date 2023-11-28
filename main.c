#include "world.h"

int main(int argc, char **argv) {
    system("/bin/stty raw onlcr");
    srand(_seed);
    World *world = createWorld(argc, argv);
    display(world, 0);
    char ch = ' ';
    while((ch = getchar()) != '.') {
        if(world->gameOver) {
            if(ch == 'r') {
                deleteWorld(world);
                world = createWorld(argc, argv);
            }
        }
        else {
            if(ch == 's') run(world);
            else if(ch == 'a') moveDropper(&(world->dr), -1);
            else if(ch == 'd') moveDropper(&(world->dr), 1);
        }
        display(world, 0);
    }
    deleteWorld(world);
    system("clear");
    system("/bin/stty cooked");
    return 0;
}
