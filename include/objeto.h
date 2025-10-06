#ifndef OBJETO_H
#define OBJETO_H

#include "algoritmos.h"
#include <stdio.h>

typedef struct Objeto {
    int id;
    double x, y;
    double largura;

    double inicioX, fimX;
} Objeto_t;

Objeto_t CriaObj(int id, double x, double y, double largura);
Objeto_t* EncontrarObj(Objeto_t* vetor, int num_objetos, int id);
void DestroiObj(Objeto_t o);
void AttPos(Objeto_t *o, double novo_x, double novo_y);

#endif // OBJETO_H