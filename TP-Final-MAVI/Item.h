#pragma once
#include <SFML/Graphics.hpp>
#include "Nave.h"
#include "Figura.h"
#include "Afichmation.h"
#include "Audio.h"
class Nave;

using namespace sf;
using namespace std;

class Item {
    Figura sprite;         
    Afichmation animacion;    
    bool recogido = false;
    bool terminado = false; 
    shared_ptr<Audio>sonidoItem;
public:
    Item(const string& texturePath, const Vector2f& pos, const string& animPath);

    virtual void aplicarEfecto(Nave& nave) = 0;

    void dibujar(RenderTarget& window);
    void actualizar(float deltaTime);

    FloatRect verBounds();
    bool estaTerminado() const { return terminado; }

    void recoger(Nave& nave);
};