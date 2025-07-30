#pragma once
#include "Enemigo.h"
#include "Nave.h"
class TorretaEspacial :public Enemigo {
    Vector2f pivot;
    float angulo;
    Vector2f dir;
    Nave* jugador = nullptr;
public:
    TorretaEspacial(const Nave* jugador, Partida* p);
    void comportamiento(float deltaTime) override;
    Vector2f verDireccionDisparo() const override;
};

