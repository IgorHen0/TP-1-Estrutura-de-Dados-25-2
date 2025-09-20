#ifndef OBJETO_H
#define OBJETO_H

#include "algoritmos.h"

// Struct para Objeto
typedef struct Objeto {
    int id;
    double x, y;
    int largura;

    int inicioX, fimX;
} Objeto_t;

Objeto_t CriaObj(int id, double x, double y, int largura);
void DestroiObj(Objeto_t o);
void AttPos(Objeto_t *o, double novo_x, double novo_y);

#endif // OBJETO_H