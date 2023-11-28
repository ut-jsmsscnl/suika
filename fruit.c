#include "fruit.h"

Fruit *createFruit(double x, double y, int type) {
    Fruit *f = (Fruit*)malloc(sizeof(Fruit));
    f->x = (Vector){x, y};
    f->xp = (Vector){NAN, NAN};
    f->v = f->j = (Vector){0., 0.};
    f->type = type;
    f->r = _fr[type];
    f->m = f->r * f->r;
    f->prev = f->next = NULL;
    return f;
}
