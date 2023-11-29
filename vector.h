#ifndef VECTOR_H_INCLUDED
#define VECTOR_H_INCLUDED
#include <math.h>

typedef struct _Vector {
    double x, y;
} Vector;

static inline Vector vecAdd(Vector a, Vector b) {
    return (Vector){a.x + b.x, a.y + b.y};
}

static inline void vecAddA(Vector *a, Vector b) {
    a->x += b.x;
    a->y += b.y;
}

static inline Vector vecSub(Vector a, Vector b) {
    return (Vector){a.x - b.x, a.y - b.y};
}

static inline void vecSubA(Vector *a, Vector b) {
    a->x -= b.x;
    a->y -= b.y;
}

static inline Vector vecMinus(Vector a) {
    return (Vector){-a.x, -a.y};
}

static inline Vector vecMult(Vector a, double k) {
    return (Vector){a.x * k, a.y * k};
}

static inline void vecMultA(Vector *a, double k) {
    a->x *= k;
    a->y *= k;
}

static inline void vecMultAddA(Vector *a, Vector b, double k) {
    a->x += b.x * k;
    a->y += b.y * k;
}

static inline double vecDot(Vector a, Vector b) {
    return a.x * b.x + a.y * b.y;
}

static inline double vecNorm2(Vector a) {
    return vecDot(a, a);
}

static inline double vecNorm(Vector a) {
    return sqrt(vecNorm2(a));
}

static inline double vecDist2(Vector a, Vector b) {
    return vecNorm2(vecSub(a, b));
}

static inline double vecDist(Vector a, Vector b) {
    return sqrt(vecDist2(a, b));
}

static inline Vector vecNormalize(Vector a) {
    if(vecNorm(a) > 0.) return vecMult(a, 1 / vecNorm(a));
    return (Vector){0., 0.};
}

static inline Vector vecCross(Vector a, double k) {
    return (Vector){-a.y * k, a.x * k};
}

#endif
