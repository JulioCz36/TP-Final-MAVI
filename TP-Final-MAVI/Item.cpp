#include "Item.h"

Item::Item(const string& texturePath, const Vector2f& pos, const string& animPath): animacion(animPath, true, 8, 8) {
    sprite.cargarImagen(texturePath);
    sprite.quePosition(pos.x, pos.y);
    animacion.setPosition(pos);
    animacion.Add("recogido", { 0,1,2,3 }, 6, false);

    sonidoItem = make_shared<Audio>();
    sonidoItem->cargar("assets/sonidos/item_up.wav");
    sonidoItem->queVolumen(50);
}

void Item::dibujar(RenderTarget& window) {
    if (recogido) {
        window.draw(animacion);
    }
    else {
        sprite.dibujar(window);
    }
}
void Item::actualizar(float deltaTime) {

    if (recogido) {
        animacion.Update();
        if (animacion.IsFinished("recogido")) {
            terminado = true;
        }
    }
}

FloatRect Item::verBounds() { return sprite.verGlobalBounds();}


void Item::recoger(Nave& nave) {
    if (!recogido) {
        sonidoItem->play();
        aplicarEfecto(nave);
        recogido = true;
        animacion.Play("recogido");
    }
}


