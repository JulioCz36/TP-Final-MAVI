#pragma once
#include <SFML/Graphics.hpp>
#include "Escenas.h"
#include "Menu.h"

using namespace sf;
using namespace std;

class MenuPrincipal : public Escena, public Menu {
    Figura titulo;

public:
    MenuPrincipal(RenderWindow& v);
    void procesoEventos(Juego& j, Event& event) override;
    void actualizar(Juego& j) override;
    void dibujar(RenderWindow& w) override;

    void ejecutarAccion(Juego& j, Opciones accion) override;
};

