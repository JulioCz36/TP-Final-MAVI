#include "ItemEscudo.h"

ItemEscudo::ItemEscudo(const Vector2f& pos)
    : Item("assets/items/item_escudo.png", pos, "assets/items/items_up_escudo.png") {
}

void ItemEscudo::aplicarEfecto(Nave& nave) {
	nave.activarEscudo(10.f);
}