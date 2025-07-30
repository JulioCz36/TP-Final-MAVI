#pragma once
#include <SFML/Graphics.hpp>
#include "utils.h"
#include "Menu.h"
using namespace sf;
using namespace std;


class PausaMenu : public Menu{
    RectangleShape fondoOscuro;
public:
    PausaMenu(RenderWindow& v);
    void ejecutarAccion(Juego& j, Opciones accion) override;
    void dibujarMenu(RenderWindow& ventana) override;
};
