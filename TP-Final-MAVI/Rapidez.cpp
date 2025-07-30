#include "Rapidez.h"

Rapidez::Rapidez(float tiempoRecarga, float duracion) : Habilidad(tiempoRecarga, duracion) {}

void Rapidez::aplicarEfecto(Nave& nave) {
    if (relojRecarga.verTiempoTranscurrido() >= tiempoRecarga) {
        activa = true;
        relojDuracion.reiniciar();
        naveRef = &nave;

        naveRef->activarInvulnerabilidad(duracion);

        if (nave.estaQuieto()) {
            nave.esVisible(false);
        }
        else {
            nave.cambiarPos(150.0);
        }
    }
}

void Rapidez::comportamiento() {
    if (activa && relojDuracion.verTiempoTranscurrido() >= 0.5f) {
        if (naveRef) {
            naveRef->esVisible(true);
        }
    }
}

string Rapidez::verRutaTextura() {
    return "assets/jugador/habilidades/velocidad_sheet.png";
}
