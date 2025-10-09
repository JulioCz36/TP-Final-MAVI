#pragma once
#include <SFML/Graphics.hpp>
#include "Escenas.h"
#include "Menu.h"
#include "Afichmation.h"

using namespace sf;
using namespace std;

class PrePartida : public Escena, public Menu {
    Figura titulo, cartel;

    Afichmation barra, mouse;
public:
    PrePartida(RenderWindow& v);
    void procesoEventos(Juego& j, Event& event) override;
    void actualizar(Juego& j) override;
    void dibujar(RenderTarget& target) override;
};

