#ifndef OBJETO_H
#define OBJETO_H

#include "algoritmos.h"

typedef struct Objeto {
    int id;
    float x, y;
    int largura;
} Objeto_t, *Objeto_ptr;

Objeto_ptr Cria();
void Destroi(Objeto_ptr o);
void AttPos(Objeto_ptr o, float x, float y);

#endif // OBJETO_H