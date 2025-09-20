#ifndef CENA_H
#define CENA_H

#include "objeto.h"

typedef struct Cena {
    int num_cena;
    int id_obj;
    int inicio, fim;
} Cena_t;

void AddObjeto(Objeto_t obj, Cena_t *cena, int num_cena);
int ObjVisivel(Objeto_t obj);
void GeraCena(Objeto_t *obj, int num_obj, Cena_t *cena, int num_cena);

#endif // CENA_H