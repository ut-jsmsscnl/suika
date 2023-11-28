#include "consts.h"

const Vector _walln[3] = {(Vector){0., -1.},
                          (Vector){1., 0.},
                          (Vector){-1., 0.}};
const double _xmax = 2.;
const double _ymax = 3;

const Vector _gravity = (Vector){0., 1.};
const double _e = .2;
const double _mu = .1;
const double _bias = .2;
const double _pdm = .01;

const int _fps = 10;
const int _subframe = 5;
const double _dt = 1. / _fps / _subframe;
