#include "../include/objeto.h"
#include <stdio.h>
#include <stdlib.h>

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