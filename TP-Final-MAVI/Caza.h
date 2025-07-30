#pragma once
#include "Enemigo.h"
#include "utils.h"
#include "Nave.h"

class Caza : public Enemigo {

    int vueltasRestantes = 3;
    int modoMovimiento = 0;
    Vector2f direccionAtaque;
    bool direccionFijada = false;
    Nave* jugador = nullptr;

public:
    Caza(const Nave* jugador);
    void comportamiento(float deltaTime) override;
};

