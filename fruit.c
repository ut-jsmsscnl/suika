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

void addFruit(Fruit **f, Fruit *newf) {
    if(*f != NULL) {
        (*f)->next = newf;
        newf->prev = *f;
    }
    *f = newf;
}

void *deleteFruit(Fruit **f, Fruit *delf) {
    if(delf->prev != NULL) delf->prev->next = delf->next;
    if(delf->next != NULL) delf->next->prev = delf->prev;
    else *f = delf->prev;
    free(delf);
}

void addColPair(ColPair **col, Fruit *f1, Fruit *f2) {
    ColPair *newcol = (ColPair*)malloc(sizeof(ColPair));
    newcol->f1 = f1;
    newcol->f2 = f2;
    if(*col != NULL) newcol->prev = *col;
    else newcol->prev = NULL;
    *col = newcol;
}
