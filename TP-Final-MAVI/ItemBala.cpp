#include "ItemBala.h"
ItemBala::ItemBala(int n_bala) 
    : Item(
    n_bala == 1 ? "assets/items/item_rapida.png" :
    n_bala == 3 ? "assets/items/item_pesada.png" :
    n_bala == 4 ? "assets/items/item_bomba.png" :
    "assets/items/item_doble.png"
    ),
    bala(n_bala)
{
    if (bala == 1) {
        cant_balas = 40;
    } else if (bala == 3) {
        cant_balas = 20;
    }
    else if (bala == 4) {
        cant_balas = 10;
    }
    else if (bala == 5) {
        cant_balas = 30;
    }
}

void ItemBala::aplicarEfecto(Nave& nave) {
    if (bala == 5) {
        nave.doubleBalaSi(cant_balas);
    }
    else {
        nave.cambiarBalas(bala, cant_balas);
    }
}