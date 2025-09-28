#include "ItemVida.h"
ItemVida::ItemVida() : Item("assets/items/item_vida.png") {}

void ItemVida::aplicarEfecto(Nave& nave) {
	nave.aumentarVida(1);
}
