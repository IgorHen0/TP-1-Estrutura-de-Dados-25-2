#include "../include/algoritmos.h"
#include "../include/objeto.h"
#include <stdio.h>
#include <stdlib.h>

void Troca(Objeto_t *o, int i, int j) {
    if(!o) {
        fprintf(stderr, "Erro: memoria nao alocada para os objetos.\n");
        return;
    }

    Objeto_t temp;

    temp = o[i];
    o[i] = o[j];
    o[j] = temp;
}

int Particao(Objeto_t *o, int inicio, int fim, int num_objs) {
    if(!o) {
        fprintf(stderr, "Erro: memoria nao alocada para os objetos.\n");
        return -1;
    }

    if(inicio < 0 || fim >= num_objs || inicio > fim) {
        fprintf(stderr, "Erro: indices invalidos.\n");
        return -1;
    }

    double pivot = o[fim].y;
    int i = inicio - 1;

    for(int j = inicio; j < fim; j++) {
        if(o[j].y <= pivot) {
            i++;
            Troca(o, i, j);
        }
    }

    Troca(o, i + 1, fim);
    return i + 1;
}

void QuickSort(Objeto_t *o, int inicio, int fim, int num_objs) {
    if(!o) {
        fprintf(stderr, "Erro: parametros invalidos.\n");
        return;
    }

    if(inicio < fim) {
        int pi = Particao(o, inicio, fim, num_objs);

        if(pi == -1) {
            fprintf(stderr, "Erro: particao falhou.\n");
            return;
        }

        // Ordena os elementos
        QuickSort(o, inicio, pi - 1, num_objs);
        QuickSort(o, pi + 1, fim, num_objs);
    }
}