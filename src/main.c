#include "../include/cena.h"
#include "../include/objeto.h"
#include "../include/algoritmos.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char linha[256];
    Objeto_t vetorObjs[MAX_TAM];
    Cena_t vetorCena[MAX_TAM * 10];
    int num_obj = 0;

    // Processa uma linha por vez da entrada padrão
    while (fgets(linha, sizeof(linha), stdin)) {
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
                sscanf(linha, " %*c %d %lf %lf %lf", &id, &x, &y, &largura);
                vetorObjs[num_obj] = CriaObj(id, x, y, largura);
                num_obj++;
            }

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
            
            int tempo;
            sscanf(linha, " %*c %d", &tempo);
            
            // Gera e imprime a cena imediatamente
            GeraCena(vetorObjs, num_obj, vetorCena, tempo);
        }
    }

    return 0;
}