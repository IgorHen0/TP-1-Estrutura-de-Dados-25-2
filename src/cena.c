#include "../include/cena.h"
#include "../include/objeto.h"
#include "../include/algoritmos.h"
#include <stdio.h>
#include <stdlib.h>

static Intervalo_t intervalo_ocluso[MAX_TAM];
static int num_intervalo_ocluso = 0;

void AdicionarIntervaloOclusao(double inicio, double fim) {
    if (num_intervalo_ocluso >= MAX_TAM) {
        return; // Impede o overflow do buffer
    }
    intervalo_ocluso[num_intervalo_ocluso].inicio = inicio;
    intervalo_ocluso[num_intervalo_ocluso].fim = fim;
    num_intervalo_ocluso++;

    QuickSortIntervalo(intervalo_ocluso, 0, num_intervalo_ocluso - 1);

    if (num_intervalo_ocluso <= 1) {
        return;
    }

    int indice_mesclado = 0;
    for (int i = 1; i < num_intervalo_ocluso; i++) {
        if (intervalo_ocluso[i].inicio <= intervalo_ocluso[indice_mesclado].fim) {
            if (intervalo_ocluso[i].fim > intervalo_ocluso[indice_mesclado].fim) {
                intervalo_ocluso[indice_mesclado].fim = intervalo_ocluso[i].fim;
            }
        } else {
            indice_mesclado++;
            intervalo_ocluso[indice_mesclado] = intervalo_ocluso[i];
        }
    }
    num_intervalo_ocluso = indice_mesclado + 1;
}

void AddObjeto(Objeto_t obj, Cena_t *cena, int *num_segmentos_na_cena, int tempo_cena) {
    double x_atual = obj.inicioX;

    while (x_atual < obj.fimX) {
        int ocluso = 0;
        for (int i = 0; i < num_intervalo_ocluso; i++) {
            if (x_atual >= intervalo_ocluso[i].inicio && x_atual < intervalo_ocluso[i].fim) {
                x_atual = intervalo_ocluso[i].fim;
                ocluso = 1;
                break;
            }
        }

        if (ocluso) continue;

        double inicio_visivel = x_atual;
        double fim_visivel = obj.fimX;
        for (int i = 0; i < num_intervalo_ocluso; i++) {
            if (intervalo_ocluso[i].inicio > inicio_visivel && intervalo_ocluso[i].inicio < fim_visivel) {
                fim_visivel = intervalo_ocluso[i].inicio;
            }
        }

        if (fim_visivel > inicio_visivel) {
            if (*num_segmentos_na_cena < MAX_TAM * 10) { // Garante que não exceda o limite do vetor de cena
                cena[*num_segmentos_na_cena].num_cena = tempo_cena;
                cena[*num_segmentos_na_cena].id_obj = obj.id;
                cena[*num_segmentos_na_cena].inicio = inicio_visivel;
                cena[*num_segmentos_na_cena].fim = fim_visivel;
                (*num_segmentos_na_cena)++;
            }
        }
        x_atual = fim_visivel;
    }
}

void GeraCena(Objeto_t *vetor_obj, int num_obj, Cena_t *vetor_cena, int tempo_cena) {

    num_intervalo_ocluso = 0;
    int num_segmentos_na_cena = 0;

    for (int i = 0; i < num_obj; i++) {
        Objeto_t obj_atual = vetor_obj[i];
        AddObjeto(obj_atual, vetor_cena, &num_segmentos_na_cena, tempo_cena);
        AdicionarIntervaloOclusao(obj_atual.inicioX, obj_atual.fimX);
    }

    QuickSortCena(vetor_cena, 0, num_segmentos_na_cena - 1, num_segmentos_na_cena);
    
    // Imprime a saída da cena
    for (int i = 0; i < num_segmentos_na_cena; i++) {
        printf("S %d %d %.2f %.2f\n",
               vetor_cena[i].num_cena,
               vetor_cena[i].id_obj,
               vetor_cena[i].inicio,
               vetor_cena[i].fim);
    }
}