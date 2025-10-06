#include "../include/objeto.h"
#include <stdio.h>
#include <stdlib.h>

// Inicializa os objetos
Objeto_t CriaObj(int id, double x, double y, double largura) {
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