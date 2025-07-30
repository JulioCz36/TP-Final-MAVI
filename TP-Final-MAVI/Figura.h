#pragma once

#include <SFML/Graphics.hpp>
using namespace sf;
using namespace std;


class Figura {
    Texture textura;
    Sprite sprite;

public:
    Figura() {};

    Figura(const Figura&) = delete;
    Figura& operator=(const Figura&) = delete;


    void cargarImagen(const string& ruta) {
        textura.loadFromFile(ruta);
        sprite.setTexture(textura);
        sprite.setOrigin(sprite.getGlobalBounds().width / 2.f, sprite.getGlobalBounds().height / 2.f);
    }


    void quePosition(float x, float y) {
        sprite.setPosition(x, y);
    }
    Vector2f verPosition() {
        return sprite.getPosition();
    }

    FloatRect verGlobalBounds() {
        return sprite.getGlobalBounds();
    }

    void dibujar(RenderWindow& ventana) {
        ventana.draw(sprite);
    }

    void queOrigin(float x, float y) {
        sprite.setOrigin(x, y);
    }

    void mover(float dx, float dy) {
        sprite.move(dx, dy);
    }

    void queEscala(float x, float y) {
        sprite.setScale(x, y);
    }

    void queColor(Color c) {
        sprite.setColor(c);
    }

    Sprite& verSprite() {
        return sprite;
    }

    void queRotation(float angle) {
        sprite.setRotation(angle);
    }

    float verRotation() const {
        return sprite.getRotation();
    }
};
