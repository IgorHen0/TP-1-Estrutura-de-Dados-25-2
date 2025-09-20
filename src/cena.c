#include "../include/cena.h"
#include "../include/objeto.h"
#include "../include/algoritmos.h"
#include <stdio.h>
#include <stdlib.h>

void GeraCena(Objeto_t *vetor_obj, int num_obj, Cena_t *vetor_cena, int num_cena) {
    QuickSort(vetor_obj, 0, num_obj - 1, num_obj);

    for(int i=0; i<num_obj; i++) {
        if(ObjVisivel(vetor_obj[i])) {
            AddObjeto(vetor_obj[i], vetor_cena, &num_cena);
        }
    }
}

ObjVisivel(Objeto_t obj) {
    
}