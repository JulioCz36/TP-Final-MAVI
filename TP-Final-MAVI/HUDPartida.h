#pragma once
#include <SFML/Graphics.hpp>
#include "Figura.h"
#include "Afichmation.h"
using namespace sf;
using namespace std;

class HUDPartida{
    Afichmation digito;
    vector<Afichmation> metros;

    vector<Figura> icon_vidas;
    int vidaMax;

    void actualizarDigitos(vector<Afichmation>& destino, int valor, int posXFin, int posY);

public:
    HUDPartida(int vidaMax);

    // ===  MÉTODOS PRINCIPALES ===
    void actualizar(int vida_t, int metros_t);
    void dibujar(RenderTarget& window);

};

