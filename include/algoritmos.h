#ifndef ALGORITMOS_H
#define ALGORITMOS_H

#include "objeto.h"
#include "cena.h"

typedef struct Objeto Objeto_t;
typedef struct Cena Cena_t;
typedef struct Intervalo Intervalo_t;

void QuickSort(Objeto_t *o, int inicio, int fim, int num_objs);
int Particao(Objeto_t *o, int inicio, int fim, int num_objs);
void Troca(Objeto_t *o, int i, int j);

void QuickSortCena(Cena_t *c, int inicio, int fim, int num_cena);
int ParticaoCena(Cena_t *c, int inicio, int fim, int num_cena);
void TrocaCena(Cena_t *c, int i, int j);

void QuickSortIntervalo(Intervalo_t *v, int inicio, int fim);
int ParticaoIntervalo(Intervalo_t *v, int inicio, int fim);
void TrocaIntervalo(Intervalo_t *v, int i, int j);

#endif // ALGORITMOS_H