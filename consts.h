#ifndef CONSTS_H_INCLUDED
#define CONSTS_H_INCLUDED
#include "vector.h"

#define _RED "\x1B[31m"
#define _GREEN "\x1B[32m"
#define _YELLOW "\x1B[33m"
#define _BLUE "\x1B[34m"
#define _MAGENTA "\x1B[35m"
#define _CYAN "\x1B[36m"
#define _DEF "\x1B[0m"

const int _seed;

const int _twidth, _theight;
const double _aspect;

const double _boundx, _boundy;

const Vector _gravity;
const double _e, _mu, _bias, _pdth;

const int _fps, _subframe;
const double _dt;

const double _maxt, _checkt;
const int _maxf, _checkf;

const double _xth, _vth;

const int _ftn, _dftn;
extern const double _fr[];
extern const int _fs[];
extern const char _fch[];
extern const char *_fcol[];
const double _limity;

const int _drstep;
const double _drxn, _drvn;

#endif
