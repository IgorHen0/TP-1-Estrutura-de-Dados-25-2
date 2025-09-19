#ifndef ALGORITMOS_H
#define ALGORITMOS_H

#include "objeto.h"

void QuickSort(Objeto_ptr *obj_ptr, int low, int high);
int Particao(Objeto_ptr *obj_ptr, int low, int high);
void Troca(Objeto_ptr *obj_ptr, int i, int j);

#endif // ALGORITMOS_H