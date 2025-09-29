#include "ItemPropulsor.h"

ItemPropulsor::ItemPropulsor(const Vector2f& pos)
    : Item("assets/items/item_propulsor.png", pos, "assets/items/items_up_propulsor.png") {
}

void ItemPropulsor::aplicarEfecto(Nave& nave) {
    nave.activarPropulsor(3.f,300.f);
}