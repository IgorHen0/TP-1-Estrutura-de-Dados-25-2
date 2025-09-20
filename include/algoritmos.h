#ifndef ALGORITMOS_H
#define ALGORITMOS_H

#include "objeto.h"

typedef struct Objeto Objeto_t;

void QuickSort(Objeto_t *o, int inicio, int fim, int num_objs);
int Particao(Objeto_t *o, int inicio, int fim, int num_objs);
void Troca(Objeto_t *o, int i, int j);

#endif // ALGORITMOS_H