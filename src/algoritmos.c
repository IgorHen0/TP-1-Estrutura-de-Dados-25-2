#include "../include/algoritmos.h"
#include "../include/objeto.h"
#include "../include/cena.h"
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

void TrocaCena(Cena_t *c, int i, int j) {
    if(!c) {
        fprintf(stderr, "Erro: memoria nao alocada para os objetos.\n");
        return;
    }

    Cena_t temp;

    temp = c[i];
    c[i] = c[j];
    c[j] = temp;
}

int ParticaoCena(Cena_t *c, int inicio, int fim, int num_cena) {
    if(!c) {
        fprintf(stderr, "Erro: memoria nao alocada para os objetos.\n");
        return -1;
    }

    if(inicio < 0 || fim >= num_cena || inicio > fim) {
        fprintf(stderr, "Erro: indices invalidos.\n");
        return -1;
    }

    Cena_t pivot = c[fim];
    int i = inicio - 1;

    for(int j = inicio; j < fim; j++) {
        if (c[j].id_obj < pivot.id_obj || (c[j].id_obj == pivot.id_obj && c[j].inicio <= pivot.inicio)) {
            i++;
            TrocaCena(c, i, j);
        }
    }

    TrocaCena(c, i + 1, fim);
    return i + 1;
}

void QuickSortCena(Cena_t *c, int inicio, int fim, int num_cena) {
    if(!c) {
        fprintf(stderr, "Erro: parametros invalidos.\n");
        return;
    }

    if(inicio < fim) {
        int pi = ParticaoCena(c, inicio, fim, num_cena);

        if(pi == -1) {
            fprintf(stderr, "Erro: particao falhou.\n");
            return;
        }

        // Ordena os elementos
        QuickSortCena(c, inicio, pi - 1, num_cena);
        QuickSortCena(c, pi + 1, fim, num_cena);
    }
}

void TrocaIntervalo(Intervalo_t *v, int i, int j) {
    Intervalo_t temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}

int ParticaoIntervalo(Intervalo_t *v, int inicio, int fim) {
    double pivot = v[fim].inicio;
    int i = inicio - 1;

    for (int j = inicio; j < fim; j++) {
        if (v[j].inicio <= pivot) {
            i++;
            TrocaIntervalo(v, i, j);
        }
    }
    TrocaIntervalo(v, i + 1, fim);
    return i + 1;
}

void QuickSortIntervalo(Intervalo_t *v, int inicio, int fim) {
    if (inicio < fim) {
        int pi = ParticaoIntervalo(v, inicio, fim);
        QuickSortIntervalo(v, inicio, pi - 1);
        QuickSortIntervalo(v, pi + 1, fim);
    }
}