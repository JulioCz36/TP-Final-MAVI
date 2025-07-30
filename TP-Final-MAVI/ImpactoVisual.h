#pragma once

#include <SFML/Graphics.hpp>
#include "Reloj.h"
using namespace sf;
using namespace std;


class ImpactoVisual {
    Sprite sprite;
    float duracion = 0.15f;
    Reloj reloj;
public:
    ImpactoVisual(Texture& tex, Vector2f pos) {
        sprite.setTexture(tex);
        sprite.setPosition(pos);
        sprite.setOrigin(sprite.getGlobalBounds().width / 2, sprite.getGlobalBounds().height / 2);
        reloj.reiniciar();
    }

    bool estaVencido(){
        return reloj.verTiempoTranscurrido() > duracion;
    }

    void dibujar(RenderWindow& w) {
        w.draw(sprite);
    }
};
