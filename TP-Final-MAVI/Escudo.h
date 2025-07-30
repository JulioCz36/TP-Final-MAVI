#pragma once
#include "Habilidad.h"
#include "Figura.h"

using namespace sf;
using namespace std;

class Escudo : public Habilidad {
    Nave* naveRef = nullptr;
    Figura spriteEscudo;
public:
    Escudo(float tiempoRecarga, float duracion);

    void aplicarEfecto(Nave& ship) override;
    void comportamiento() override;
    string verRutaTextura() override;
    void dibujar(RenderWindow& w) override;
};


