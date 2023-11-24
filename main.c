#include "world.h"

int main(int argc, char **argv) {
    World *world = createWorld();
    addFruit(world, createFruit(1., 1.6, 0.4));
    addFruit(world, createFruit(0.2, 2.2, 0.2));
    run(world);
    destroyWorld(world);
    return 0;
}
