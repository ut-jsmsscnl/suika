#include "world.h"

int main(int argc, char **argv) {
    World *world = createWorld();
    addFruit(world, createFruit(0.2, 2.0, 0.15, '1'));
    addFruit(world, createFruit(0.5, 1.0, 0.3, '2'));
    addFruit(world, createFruit(1.0, 0.2, 0.2, '3'));
    addFruit(world, createFruit(1.2, 2.0, 0.15, '4'));
    addFruit(world, createFruit(1.4, 0.8, 0.4, '5'));
    run(world);
    destroyWorld(world);
    return 0;
}
