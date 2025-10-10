#include "../include/cena.h"
#include "../include/objeto.h"
#include "../include/algoritmos.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// #define ORDENAR_SEMPRE
// #define ORDENAR_COM_LIMIAR
#define ORDENAR_NA_CENA

#ifdef ORDENAR_COM_LIMIAR
    const int LIMIAR_DESORGANIZACAO = 50;
#endif

int main() {

    clock_t start = clock();

    char linha[256];
    Objeto_t vetorObjs[MAX_TAM];
    Cena_t vetorCena[MAX_TAM * 10];
    int num_obj = 0;
    int contador_desorganizacao = 0;
    int numero_linha = 0;

    // Processa uma linha por vez da entrada padrão
    while (fgets(linha, sizeof(linha), stdin)) {
        numero_linha++;
        // Ignora linhas em branco
        if (linha[0] == '\n' || linha[0] == '\r') {
            continue;
        }
        
        char tipo_linha = linha[0];

        if (tipo_linha == 'O') {
            // Verifica se ainda há espaço no vetor de objetos
            if (num_obj < MAX_TAM) {
                int id;
                double x, y, largura;
                int itens_lidos = sscanf(linha, " %*c %d %lf %lf %lf", &id, &x, &y, &largura);
                if (itens_lidos != 4) {
                    fprintf(stderr, "Aviso: Linha %d malformada. Esperado 'O id x y largura'.\n", numero_linha);
                    continue;
                }
                vetorObjs[num_obj] = CriaObj(id, x, y, largura);
                num_obj++;
            }

        } else if (tipo_linha == 'M') {
            if (num_obj == 0) continue; // Não faz nada se não houver objetos

            int tempo, id;
            double novo_x, novo_y;
            int itens_lidos = sscanf(linha, " %*c %d %d %lf %lf", &tempo, &id, &novo_x, &novo_y);
            if (itens_lidos != 4) {
                fprintf(stderr, "Aviso: Linha %d malformada. Esperado 'M tempo id novo_x novo_y'.\n", numero_linha);
                continue;
            }

            int indice_obj_movido = -1;
            for(int i=0; i<num_obj; i++) {
                if(vetorObjs[i].id == id) {
                    indice_obj_movido = i;
                    break;
                }
            }

            if (indice_obj_movido != -1) {
                // Salva a posição y antiga para calcular a métrica de desorganização
                double y_antigo = vetorObjs[indice_obj_movido].y;
                
                AttPos(&vetorObjs[indice_obj_movido], novo_x, novo_y);

                // Cálculo da Métrica de Desorganização
                if (indice_obj_movido > 0 && 
                    vetorObjs[indice_obj_movido].y < vetorObjs[indice_obj_movido - 1].y && 
                    y_antigo >= vetorObjs[indice_obj_movido - 1].y) {
                    contador_desorganizacao++;
                }

                if (indice_obj_movido < num_obj - 1 && 
                    vetorObjs[indice_obj_movido].y > vetorObjs[indice_obj_movido + 1].y && 
                    y_antigo <= vetorObjs[indice_obj_movido + 1].y) {
                    contador_desorganizacao++;
                }
            } else {
                 fprintf(stderr, "Aviso: Objeto com id %d nao encontrado para movimentacao na linha %d.\n", id, numero_linha);
            }

            #ifdef ORDENAR_SEMPRE
                QuickSort(vetorObjs, 0, num_obj-1, num_obj);
            #elif defined(ORDENAR_COM_LIMIAR)
                if(contador_desorganizacao >= LIMIAR_DESORGANIZACAO) {
                    QuickSort(vetorObjs, 0, num_obj-1, num_obj);
                    contador_desorganizacao = 0;
                }
            #endif

        } else if (tipo_linha == 'C') {
            if (num_obj == 0) continue; // Não gera cena se não houver objetos
            
            int tempo;
            int itens_lidos = sscanf(linha, " %*c %d", &tempo);
            if (itens_lidos != 1) {
                fprintf(stderr, "Aviso: Linha %d malformada. Esperado 'C tempo'.\n", numero_linha);
                continue;
            }

            #ifdef ORDENAR_NA_CENA
                QuickSort(vetorObjs, 0, num_obj-1, num_obj);
            #endif
            
            // Gera e imprime a cena imediatamente
            GeraCena(vetorObjs, num_obj, vetorCena, tempo);
        }
    }

    clock_t end = clock();
    double tempo_cpu = (double) (end - start) / CLOCKS_PER_SEC;
    fprintf(stderr, "Tempo de execucao: %f segundos.", tempo_cpu);

    return 0;
}