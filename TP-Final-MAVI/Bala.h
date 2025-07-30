#pragma once
#include <SFML/Graphics.hpp>
#include "Figura.h"

using namespace sf;
using namespace std;

class Bala{
    Figura bala;
    int tipo;
    float velocidad, dano;
    Vector2f direccion;

public:

    Bala(int tipo, Vector2f position, Vector2f dir, bool color);

    void actualizar();
    void dibujar(RenderWindow& window);

    Sprite& verSprite();

    bool fueraDePantalla();

    FloatRect verBounds() ;
    float verDano();

    int verTipo();

};
