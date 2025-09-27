#pragma once
#include <SFML/Graphics.hpp>
#include "utils.h"
#include "Menu.h"
using namespace sf;
using namespace std;


class PausaMenu : public Menu{
    RectangleShape fondoOscuro;
    Figura titulo;
public:
    PausaMenu(RenderWindow& v);
    void dibujarMenu(RenderTarget& ventana) override;
};
