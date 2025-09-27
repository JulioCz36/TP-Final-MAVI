#include "Item.h"

Item::Item(const string& texturePath) : textura(texturePath) {
    item.cargarImagen(textura);
    item.quePosition(rand() % 1240, -40);
}

void Item::dibujar(RenderTarget& window) {
    item.dibujar(window);
}
void Item::actualizar(float deltaTime) {
    item.mover(0, 100.f * deltaTime);
}

bool Item::mostrarEnHUD(){ return true; }
string Item::verItem() const {return textura;}

FloatRect Item::verBounds() { return item.verGlobalBounds(); }
bool Item::fueraDePantalla() {
    return item.verPosition().y > 720;
}


