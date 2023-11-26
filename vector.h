#ifndef VECTOR_H_INCLUDED
#define VECTOR_H_INCLUDED
#include <math.h>

typedef struct _Vector {
    double x, y;
} Vector;

Vector vecAdd(Vector a, Vector b) {
    return (Vector){a.x + b.x, a.y + b.y};
}

void vecAddA(Vector *a, Vector b) {
    a->x += b.x;
    a->y += b.y;
}

Vector vecSub(Vector a, Vector b) {
    return (Vector){a.x - b.x, a.y - b.y};
}

void vecSubA(Vector *a, Vector b) {
    a->x -= b.x;
    a->y -= b.y;
}

Vector vecMult(Vector a, double k) {
    return (Vector){a.x * k, a.y * k};
}

void vecMultA(Vector *a, double k) {
    a->x *= k;
    a->y *= k;
}

void vecMultAddA(Vector *a, Vector b, double k) {
    a->x += b.x * k;
    a->y += b.y * k;
}

double vecDot(Vector a, Vector b) {
    return a.x * b.x + a.y * b.y;
}

double vecNorm2(Vector a) {
    return vecDot(a, a);
}

double vecNorm(Vector a) {
    return sqrt(vecNorm2(a));
}

double vecDist2(Vector a, Vector b) {
    return vecNorm2(vecSub(a, b));
}

double vecDist(Vector a, Vector b) {
    return sqrt(vecDist2(a, b));
}

Vector vecNormalize(Vector a) {
    if(vecNorm(a) > 0.) return vecMult(a, 1 / vecNorm(a));
    return (Vector){0., 0.};
}

int vecDistCloserThan(Vector a, Vector b, double r) {
    return vecDist2(a, b) < r * r;
}

#endif
