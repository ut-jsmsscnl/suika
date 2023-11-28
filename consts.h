#ifndef CONSTS_H_INCLUDED
#define CONSTS_H_INCLUDED
#include "vector.h"

const int _seed;

const Vector _boundn[3];
const double _boundx, _boundy;

const Vector _gravity;
const double _e, _mu, _bias, _pdm;

const int _fps, _subframe;
const double _dt;

const double _maxt, _checkt, _stopth;
const int _maxf, _checkf;

const int _ftn, _dftn;
const double _fr[5];
const char _fc[5];

const int _drstep;
const double _drnr;

#endif
