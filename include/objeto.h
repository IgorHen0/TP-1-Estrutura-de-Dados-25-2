#ifndef OBJETO_H
#define OBJETO_H

#include "algoritmos.h"
#include <stdio.h>

// Struct para Objeto
typedef struct Objeto {
    int id;
    double x, y;
    int largura;

    int inicioX, fimX;
} Objeto_t;

Objeto_t CriaObj(int id, double x, double y, int largura);
Objeto_t* EncontrarObj(Objeto_t* vetor, int num_objetos, int id);
void DestroiObj(Objeto_t o);
void AttPos(Objeto_t *o, double novo_x, double novo_y);
int NumObjs(FILE *arquivo, char *nome_arquivo);
// void OrdenaPorY(Objeto_t *o, int num_objs);

#endif // OBJETO_H