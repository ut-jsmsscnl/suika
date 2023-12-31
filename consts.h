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

extern const int _seed;

extern const int _twidth, _theight;
extern const double _aspect;

extern const double _boundx, _boundy;

extern const Vector _gravity;
extern const double _e, _mu, _bias, _pdth;

extern const int _fps, _subframe;
extern const double _dt;

extern const double _maxt, _checkt;
extern const int _maxf, _checkf;
extern const double _xth, _vth;

extern const int _ftn, _dftn;
extern const double _fr[];
extern const int _fs[];
extern const char _fch[];
extern const char *_fcol[];

extern const int _drstep;
extern const double _drxn, _drvn;

#endif
