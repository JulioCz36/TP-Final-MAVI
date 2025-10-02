#pragma once
#include <SFML/Graphics.hpp>
#include "Nave.h"
#include "Figura.h"
#include "Afichmation.h"

using namespace sf;
using namespace std;


class UIPartida{
    RenderWindow& ventana;
    shared_ptr<Afichmation> botonSalto;
    Nave* jugador;
    Figura tablero;
    Vector2f transformarMouse();
public:
    UIPartida(RenderWindow& v, Nave* j);

    void manejarEventos(Event& e);
    void actualizar();
    void dibujar(RenderTarget& w);
};

