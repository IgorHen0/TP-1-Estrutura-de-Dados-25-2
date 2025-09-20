#include "../include/cena.h"
#include "../include/objeto.h"
#include "../include/algoritmos.h"
#include <stdio.h>
#include <stdlib.h>

// Função para encontrar o objeto que irá se movimentar
Objeto_t* EncontrarObj(Objeto_t* vetor, int num_objetos, int id) {
    for (int i = 0; i < num_objetos; i++) {
        if (vetor[i].id == id) {
            return &vetor[i];
        }
    }
    return NULL;
}

int main(int argc, char *argv[]) {

    if(argc < 2) {
        printf("Uso: %s <arquivo_de_entrada>\n", argv[0]);
        return 1;
    }

    char *nome_arquivo = argv[1];
    FILE *arquivo;
    char linha[256];

    int num_obj = 0;

    arquivo = fopen(nome_arquivo, "r");
    if(arquivo == NULL) {
        perror("Erro ao abrir arquivo.");
        return 1;
    }

    // Obtem quantos objetos tem na cena
    while(fgets(linha, sizeof(linha), arquivo)) {
        if(linha[0] == 'O') {
            num_obj++;
        }
    }
    fclose(arquivo);

    printf("Arquivo contem %d objetos\n", num_obj);

    if(num_obj == 0) {
        printf("Nenhum objeto encontrado.\n");
        return 0;
    }

    // Aloca memória para os objetos
    Objeto_t *vetorObjs = (Objeto_t*)malloc(num_obj * sizeof(Objeto_t));
    if(vetorObjs == NULL){
        perror("Erro ao alocar memoria para o vetor de objetos.");
        return 1;
    }

    arquivo = fopen(nome_arquivo, "r");
    if(arquivo == NULL) {
        perror("Erro ao reabrir o arquivo.");
        free(vetorObjs);
        return 1;
    }

    int indice_obj_atual = 0;
    while (fgets(linha, sizeof(linha), arquivo)) {
        char tipo_linha;

        sscanf(linha, " %c", &tipo_linha);

        if(tipo_linha == 'O') {
            int id;
            double x, y;
            int largura;

            sscanf(linha, " %*c %d %lf %lf %d", &id, &x, &y, &largura);

            if(indice_obj_atual < num_obj) {
                vetorObjs[indice_obj_atual] = CriaObj(id, x, y, largura);
                indice_obj_atual++;
            }
        }
        else if(tipo_linha == 'M') {
            int tempo, id;
            double novo_x, novo_y;

            sscanf(linha, " %*c %d %d %lf %lf", &tempo, &id, &novo_x, &novo_y);

            Objeto_t *obj_para_mover = EncontrarObj(vetorObjs, num_obj, id);
            if(obj_para_mover != NULL) {
                AttPos(obj_para_mover, novo_x, novo_y);
            }
        }
        else if(tipo_linha == 'C') {
            int tempo;

            sscanf(linha, " %*c %d", &tempo);

            printf("Gerando cena para o tempo %d\n", tempo);
        }
    }

    fclose(arquivo);

    free(vetorObjs);

    return 0;
    
}