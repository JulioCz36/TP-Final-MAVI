#include "ItemPuntos.h"
ItemPuntos::ItemPuntos() : Item("assets/items/item_punto.png") {}
bool ItemPuntos::mostrarEnHUD() { return false; }

void ItemPuntos::aplicarEfecto(Nave& nave) {
	nave.aumentarPuntos(15);
}
