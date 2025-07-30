#include "DroneDoble.h"
#include "utils.h"
#include "Partida.h"

DroneDoble::DroneDoble(Partida* p) :Enemigo(p, "assets/enemigos/drone_doble.png", 102, 85, { 0 }, { 0}, {0}, 200.0f, 35, 1.3f, 2) {
}

void DroneDoble::comportamiento(float deltaTime) {
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

void DroneDoble::disparar() {
    if (cadenciaDisparo <= 0.f) return;

    relojDisparo.reiniciar();
    sonidoDisparo.play();
    enemigo.Play("shot");

    Vector2f dirNormal = normalizar(verDireccionDisparo());

    Vector2f bulletPosition(verPosition().x - 20, verPosition().y + verBounds().height / 2);
    partida->agregarLasersEnemigos(make_unique<Bala>(danio, bulletPosition, dirNormal, false));

    Vector2f bulletPosition2(verPosition().x + 20, verPosition().y + verBounds().height / 2);
    partida->agregarLasersEnemigos(make_unique<Bala>(danio, bulletPosition2, dirNormal, false));

}



