#include "consts.h"

const int _seed = 20231129;

const int _twidth = 120;
const int _theight = 30;
const double _aspect = 2.;

const double _boundx = 2.;
const double _boundy = 3.;

const Vector _gravity = (Vector){0., 3.};
const double _e = .2;
const double _mu = .1;
const double _bias = .2;
const double _pdth = .01;

const int _fps = 10;
const int _subframe = 10;
const double _dt = 1. / _fps / _subframe;

const double _maxt = 10.;
const double _checkt = 1.;
const int _maxf = (int)(_maxt * _fps);
const int _checkf = (int)(_checkt * _fps);
const double _xth = .05;
const double _vth = .1;

const int _ftn = 8;
const int _dftn = 4;
const double _fr[] = {.12, .15, .2, .25, .3, .35, .4, .5};
const int _fs[] = {50, 150, 300, 750, 1500, 3000, 7500, 20000};
const char _fch[] = {'1', '2', '3', '4', '5', '6', '7', '8'};
const char *_fcol[] = {_BLUE, _RED, _CYAN, _MAGENTA,
                       _BLUE, _RED, _YELLOW, _GREEN};

const int _drstep = 32;
const double _drxn = .02;
const double _drvn = .01;
