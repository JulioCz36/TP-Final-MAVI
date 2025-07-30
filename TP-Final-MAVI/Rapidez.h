#pragma once
#include "Habilidad.h"

using namespace sf;
using namespace std;

class Rapidez : public Habilidad {
    Nave* naveRef = nullptr;
public:
    Rapidez(float tiempoRecarga, float duracion);

    void aplicarEfecto(Nave& ship) override;
    void comportamiento() override;
    string verRutaTextura() override;
};

