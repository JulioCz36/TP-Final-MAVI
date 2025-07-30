#pragma once
#include "Enemigo.h"
#include "Nave.h"

class DroneDoble : public Enemigo {

    float movimientoTiempo = 0;
    float movimientoDuracion = 1.3f;
    float direccionX = 1.0f;


public:
    DroneDoble(Partida* p);

    void comportamiento(float deltaTime) override;
    void disparar() override;
};

