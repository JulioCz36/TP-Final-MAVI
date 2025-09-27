#pragma once
#include <SFML/Graphics.hpp>
#include "Nave.h"
#include "Figura.h"
class Nave;

using namespace sf;
using namespace std;

class Item {
    Figura item;
    string textura;
public:
    Item(const string& texturePath);

    virtual void aplicarEfecto(Nave& nave) = 0;

    void dibujar(RenderTarget& window);
    void actualizar(float deltaTime);

    virtual bool mostrarEnHUD();
    string verItem() const;

    FloatRect verBounds();
    bool fueraDePantalla() ;
};