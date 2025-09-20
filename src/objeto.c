#include "../include/objeto.h"
#include <stdio.h>
#include <stdlib.h>

// Inicializa os objetos
Objeto_t CriaObj(int id, double x, double y, int largura) {
    Objeto_t o;
    o.id = id;
    o.x = x;
    o.y = y;
    o.largura = largura;

    o.inicioX = x - (largura/2.0f);
    o.fimX = x + (largura/2.0f);

    return o;
}

// Função para encontrar o objeto que irá se movimentar
Objeto_t* EncontrarObj(Objeto_t* vetor, int num_objetos, int id) {
    for (int i = 0; i < num_objetos; i++) {
        if (vetor[i].id == id) {
            return &vetor[i];
        }
    }
    return NULL;
}

int NumObjs(FILE *arquivo, char *nome_arquivo) {
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

    return num_obj;
}

// Atualiza a posição dos objetos
void AttPos(Objeto_t *o, double novo_x, double novo_y) {
    if(o == NULL) {
        return;
    }

    o->x = novo_x;
    o->y = novo_y;

    o->inicioX = novo_x - (o->largura/2.0f);
    o->fimX = novo_x + (o->largura/2.0f);
}

// void DestroiObj(Objeto_ptr o) {
//     if (!o) return;
    

// }