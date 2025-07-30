#include "ItemVida.h"
ItemVida::ItemVida() : Item("assets/items/item_vida.png") {}

bool ItemVida::mostrarEnHUD(){ return false; }

void ItemVida::aplicarEfecto(Nave& nave) {
	nave.aumentarVida(10);
}
