#include "world.h"

int main(int argc, char **argv) {
    World *world = createWorld();
    run(world);
    destroyWorld(world);
    return 0;
}
