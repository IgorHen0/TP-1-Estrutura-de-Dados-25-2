#ifndef ALGORITMOS_H
#define ALGORITMOS_H

#include "objeto.h"

typedef struct Objeto Objeto_t;

void QuickSort(Objeto_t obj, int low, int high);
int Particao(Objeto_t obj, int low, int high);
void Troca(Objeto_t obj, int i, int j);

#endif // ALGORITMOS_H