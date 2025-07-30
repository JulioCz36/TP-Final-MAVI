#include "Caza.h"
Caza::Caza(const Nave* player) : Enemigo("assets/enemigos/caza_sheet.png", 82, 84, { 0 }, {0}, {1}, 300.0f, 25, 0.0f, 0) {
    queDanoColision(15.0f);
    jugador = const_cast<Nave*>(player);
}

void Caza::comportamiento(float deltaTime) {
    switch (modoMovimiento) {
    case 0: {
        static float tiempoZigzag = 0.f;
        static float direccionX = 1.f;
        tiempoZigzag += deltaTime;

        if (tiempoZigzag >= 0.5f) {
            direccionX *= -1.f;
            tiempoZigzag = 0.f;
            vueltasRestantes--;
            if (vueltasRestantes <= 0)
                modoMovimiento = 1;
        }

        Vector2f movimiento(direccionX * verVelocidad() * 0.4f * deltaTime, verVelocidad() * 0.1f * deltaTime);
        mover(movimiento);
        break;
    }

    case 1: {
        if (!direccionFijada && jugador) {
            Vector2f dir = jugador->verPos() - verPosition();
            direccionAtaque = normalizar(dir);
            direccionFijada = true;
        }

        mover(direccionAtaque * verVelocidad() * deltaTime);
        break;
        }
    }
}


