#include "../include/cena.h"
#include "../include/objeto.h"
#include "../include/algoritmos.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char linha[256];
    Objeto_t *vetorObjs = NULL;
    Cena_t *vetorCena = NULL;
    int num_obj = 0;
    int capacidade_objs = 0;

    // Processa uma linha por vez da entrada padrão (teclado)
    while (fgets(linha, sizeof(linha), stdin)) {
        // Ignora linhas em branco
        if (linha[0] == '\n' || linha[0] == '\r') {
            continue;
        }
        
        char tipo_linha = linha[0];

        if (tipo_linha == 'O') {
            // Aumenta a capacidade do vetor de objetos se necessário
            if (num_obj >= capacidade_objs) {
                capacidade_objs = (capacidade_objs == 0) ? 10 : capacidade_objs * 2;
                vetorObjs = (Objeto_t*)realloc(vetorObjs, capacidade_objs * sizeof(Objeto_t));
                if (vetorObjs == NULL) {
                    perror("Erro ao realocar memoria para o vetor de objetos.");
                    return 1;
                }
            }
            
            int id;
            double x, y, largura;
            sscanf(linha, " %*c %d %lf %lf %lf", &id, &x, &y, &largura);
            vetorObjs[num_obj] = CriaObj(id, x, y, largura);
            num_obj++;

        } else if (tipo_linha == 'M') {
            if (num_obj == 0) continue; // Não faz nada se não houver objetos

            int tempo, id;
            double novo_x, novo_y;
            sscanf(linha, " %*c %d %d %lf %lf", &tempo, &id, &novo_x, &novo_y);
            Objeto_t *obj_para_mover = EncontrarObj(vetorObjs, num_obj, id);
            if (obj_para_mover != NULL) {
                AttPos(obj_para_mover, novo_x, novo_y);
            }

        } else if (tipo_linha == 'C') {
            if (num_obj == 0) continue; // Não gera cena se não houver objetos
            
            // Aloca/realoca o vetor da cena. É seguro fazer isso aqui.
            vetorCena = (Cena_t*)realloc(vetorCena, num_obj * 10 * sizeof(Cena_t));
             if (vetorCena == NULL) {
                perror("Erro ao alocar memoria para o vetor da cena.");
                free(vetorObjs);
                return 1;
            }

            int tempo;
            sscanf(linha, " %*c %d", &tempo);
            
            // Gera e imprime a cena imediatamente
            GeraCena(vetorObjs, num_obj, vetorCena, tempo);
        }
    }

    // Libera a memória alocada ao final do programa
    free(vetorObjs);
    free(vetorCena);

    return 0;
}