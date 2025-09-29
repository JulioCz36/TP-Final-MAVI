#include "ItemVida.h"
ItemVida::ItemVida(const Vector2f& pos) : Item("assets/items/item_vida.png", pos, "assets/items/items_up_vida.png") {}

void ItemVida::aplicarEfecto(Nave& nave) {
	nave.aumentarVida(1);
}
