#ifndef CENA_H
#define CENA_H

#include "objeto.h"

typedef struct Cena {
    int tempo;
    int id_obj;
    int inicio, fim;
} Cena_t, *Cena_ptr;

void AddObjeto(Objeto_t obj, Cena_ptr cena, int num_cena);
void GeraCena(Objeto_t obj, int num_obj, Cena_ptr cena, int num_cena);

#endif // CENA_H