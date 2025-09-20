#ifndef CENA_H
#define CENA_H

#include "objeto.h"

typedef struct Cena {
    int num_cena;
    int id_obj;
    int inicio, fim;
} Cena_t;

typedef struct Intervalo {
    double inicio, fim;
} Intervalo_t;

void AddObjeto(Objeto_t obj, Cena_t *cena, int *num_cena, int tempo_cena);
int ObjVisivel(Objeto_t obj);
void GeraCena(Objeto_t *obj, int num_obj, Cena_t *cena, int num_cena);
void AdicionarIntervaloOclusao(double inicio, double fim);

#endif // CENA_H