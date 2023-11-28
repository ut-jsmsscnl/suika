#include "world.h"

int main(int argc, char **argv) {
    char ch = ' ';
    World *world = createWorld();
    system("/bin/stty raw onlcr");
    while((ch = getchar()) != '.') {
        if(ch == 's') run(world);
        else if(ch == 'a') moveDropper(&(world->dr), -1);
        else if(ch == 'd') moveDropper(&(world->dr), 1);
        else if(ch == '1') deleteFruit(&(world->f), world->f->prev->prev);
        else if(ch == '2') deleteFruit(&(world->f), world->f->prev);
        else if(ch == '3') deleteFruit(&(world->f), world->f);
        display(world, 0);
    }
    system("clear");
    system("/bin/stty cooked");
    deleteWorld(world);
    return 0;
}
