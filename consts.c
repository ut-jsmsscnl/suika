#include "consts.h"

const int _seed = 20231129;

const int _twidth = 120;
const int _theight = 25;
const double _aspect = 2.5333;

const Vector _boundn[3] = {(Vector){0., -1.},
                           (Vector){1., 0.},
                           (Vector){-1., 0.}};
const double _boundx = 2.;
const double _boundy = 3.;

const Vector _gravity = (Vector){0., 3.};
const double _e = .2;
const double _mu = .1;
const double _bias = .2;
const double _pdm = .01;

const int _fps = 10;
const int _subframe = 5;
const double _dt = 1. / _fps / _subframe;

const double _maxt = 10.;
const double _checkt = 1.;
const double _xth = .1;
const double _vth = .2;
const int _maxf = (int)(_maxt * _fps);
const int _checkf = (int)(_checkt * _fps);

const int _ftn = 8;
const int _dftn = 4;
const double _fr[] = {.12, .15, .2, .25, .3, .35, .4, .5};
const char _fc[] = {'1', '2', '3', '4', '5', '6', '7', '8'};
const int _fs[] = {50, 150, 300, 750, 1500, 3000, 7500, 20000};
const double _limity = 2 * _fr[_dftn - 1] + _fr[_ftn - 1];

const int _drstep = 32;
const double _drnr = .01;
