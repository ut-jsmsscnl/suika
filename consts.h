#ifndef CONSTS_H_INCLUDED
#define CONSTS_H_INCLUDED
#include "vector.h"

const int _seed;

const int _twidth, _theight;
const double _aspect;

const Vector _boundn[3];
const double _boundx, _boundy;

const Vector _gravity;
const double _e, _mu, _bias, _pdm;

const int _fps, _subframe;
const double _dt;

const double _maxt, _checkt, _xth, _vth;
const int _maxf, _checkf;

const int _ftn, _dftn;
extern const double _fr[];
extern const char _fc[];
extern const int _fs[];
const double _limity;

const int _drstep;
const double _drnr;

#endif
