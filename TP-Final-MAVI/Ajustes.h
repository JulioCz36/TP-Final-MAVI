#pragma once
#include <SFML/Graphics.hpp>
#include "Escenas.h"
#include "Menu.h"
#include "Afichmation.h"

using namespace sf;
using namespace std;

class Ajustes : public Escena, public Menu {
    Figura titulo, cartel;
public:
    Ajustes(RenderWindow& v);
    void procesoEventos(Juego& j, Event& event) override;
    void actualizar(Juego& j) override;
    void dibujar(RenderTarget& target) override;
};

