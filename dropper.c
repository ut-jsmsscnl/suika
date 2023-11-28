#include "dropper.h"
#include <stdio.h>
void resetDropper(Dropper *dr) {
    dr->f = createFruit(_boundx / 2, 0., rand() % _dftn);
    dr->x = _drstep / 2;
}

void moveDropper(Dropper *dr, int dir) {
    if(dir == -1 && dr->x > 0) dr->x--;
    else if(dir == 1 && dr->x < _drstep) dr->x++;
    double xst = (double)dr->x / _drstep;
    double noise = _drnr * ((double)rand() / RAND_MAX - .5);
    double r = dr->f->r;
    dr->f->x.x = (_boundx - 2 * r) * (xst + noise) + r;
}
