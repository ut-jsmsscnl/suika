#include "dropper.h"

void resetDropper(Dropper *dr) {
    dr->xs = _drstep / 2;
    Vector x = (Vector){NAN, _fr[_dftn - 1]};
    Vector v = (Vector){0., 0.};
    dr->f = createFruit(x, v, rand() % _dftn);
    dr->f->x.x = getx(dr);
}

void moveDropper(Dropper *dr, int dir) {
    if(dir == -1 && dr->xs > 0) dr->xs--;
    else if(dir == 1 && dr->xs < _drstep) dr->xs++;
    dr->f->x.x = getx(dr);
}

double getx(Dropper *dr) {
    double xstd = (double)dr->xs / _drstep;
    double noise = _drnr * ((double)rand() / RAND_MAX - .5);
    double r = dr->f->r;
    return (_boundx - 2 * r) * (xstd + noise) + r;
}
