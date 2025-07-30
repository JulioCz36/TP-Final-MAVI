#include "DroneLigero.h"

DroneLigero::DroneLigero(Partida* p) : Enemigo(p,"assets/enemigos/drone_sheet.png", 93, 84, { 0 }, { 0,1,2,3,4,5,6,7,8 }, {9}, 250.0f, 25, 1.2f, 1) {
}

void DroneLigero::comportamiento(float deltaTime) {
    // Cambia dirección horizontal cada cierto tiempo
    movimientoTiempo += deltaTime;
    if (movimientoTiempo >= movimientoDuracion) {
        direccionX *= -1.0f;
        movimientoTiempo = 0.0f;
    }

    // Movimiento
    Vector2f movimiento(direccionX * verVelocidad() * 0.6f * deltaTime, verVelocidad() * 0.15f * deltaTime);
    mover(movimiento);

}