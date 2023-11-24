#ifndef VECTOR_H_INCLUDED
#define VECTOR_H_INCLUDED

typedef struct _Vector {
    double x, y;
} Vector;

void vecMultAdd(Vector *a, Vector b, double k) {
    a->x += b.x * k;
    a->y += b.y * k;
}

double vecDist2(Vector a, Vector b) {
    double dx = a.x - b.x;
    double dy = a.y - b.y;
    return dx * dx + dy * dy;
}

#endif
