#pragma once
#include "Enemigo.h"

class DroneLigero : public Enemigo {

    float movimientoTiempo = 0;
    float movimientoDuracion = 1.5f;
    float direccionX = 1.0f;

public:
    DroneLigero(Partida* p);

    void comportamiento(float deltaTime) override;
};

