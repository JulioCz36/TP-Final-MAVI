#pragma once
#include <SFML/Graphics.hpp>
#include "Figura.h"
#include "Afichmation.h"
using namespace sf;
using namespace std;

class HUDPartida{
    Afichmation digito;
    vector<Afichmation> kilometros;

    vector<Figura> icon_vidas;
    int vidaMax;

    void actualizarDigitos(vector<Afichmation>& destino, int valor, int posXInicio, int posY, bool izquierdaADerecha);

public:
    HUDPartida(int vidaMax);

    // ===  MÉTODOS PRINCIPALES ===
    void actualizar(int vida_t, int puntos_t);
    void dibujar(RenderTarget& window);

};

