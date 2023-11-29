#include "fruit.h"

Fruit *createFruit(Vector x, Vector v, int type) {
    Fruit *f = (Fruit*)malloc(sizeof(Fruit));
    f->x = x;
    f->xp = (Vector){NAN, NAN};
    f->v = v;
    f->type = type;
    f->r = _fr[type];
    f->m = f->r * f->r;
    f->prev = f->next = NULL;
    return f;
}

void addFruit(Fruit **f, Fruit *newf) {
    newf->prev = *f;
    if(*f != NULL) (*f)->next = newf;
    *f = newf;
}

void deleteFruit(Fruit **f, Fruit *delf) {
    if(delf->prev != NULL) delf->prev->next = delf->next;
    if(delf->next != NULL) delf->next->prev = delf->prev;
    else *f = delf->prev;
    free(delf);
}

void addColPair(ColPair **col, Fruit *f1, Fruit *f2) {
    ColPair *newcol = (ColPair*)malloc(sizeof(ColPair));
    newcol->active = 1;
    newcol->f1 = f1;
    newcol->f2 = f2;
    newcol->prev = *col;
    if(*col != NULL) (*col)->next = newcol;
    *col = newcol;
}
