#include "dropper.h"

void resetDropper(Dropper *dr) {
    dr->xs = _drstep / 2;
    Vector x = (Vector){NAN, _fr[_dftn - 1]};
    Vector v = (Vector){randRange(_drvn), randRange(_drvn)};
    dr->f = createFruit(x, v, randInt(_dftn));
    dr->f->x.x = getx(dr);
}

void moveDropper(Dropper *dr, int dir) {
    if(dir == -1 && dr->xs > 0) dr->xs--;
    else if(dir == 1 && dr->xs < _drstep) dr->xs++;
    dr->f->x.x = getx(dr);
}

double getx(Dropper *dr) {
    double xstd = (double)dr->xs / _drstep;
    double noise = randRange(_drxn);
    double r = dr->f->r;
    return (_boundx - 2 * r) * (xstd + noise) + r;
}
