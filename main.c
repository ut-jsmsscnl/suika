#include "world.h"

int main(int argc, char **argv) {
    World *world = createWorld();
    addFruit(world, createFruit(0.8, 2.0, 0.2, '*'));
    addFruit(world, createFruit(1.2, 0.0, 0.2, '.'));
    addFruit(world, createFruit(1.2, 1.0, 0.4, '-'));
    addFruit(world, createFruit(0.4, 0.0, 0.4, '0'));
    addFruit(world, createFruit(1.6, 2.0, 0.4, '+'));
    run(world);
    destroyWorld(world);
    return 0;
}
