#include "Habilidad.h"
Habilidad::Habilidad(float tiempoRecarga, float duracion) : tiempoRecarga(tiempoRecarga), duracion(duracion){}

bool Habilidad::estaActiva() {
    return activa;
}
bool Habilidad::estaRecargada(){
    return relojRecarga.verTiempoTranscurrido() >= tiempoRecarga;
}
float Habilidad::recarga() const {
    return min(relojRecarga.verTiempoTranscurrido() / tiempoRecarga, 1.0f);
}
void Habilidad::actualizar() {

    if (activa) {
        habilidadProgreso = 1.0f;

        if (relojDuracion.verTiempoTranscurrido() >= duracion) {
            activa = false;
            relojRecarga.reiniciar();
        }
    }
    else {
        habilidadProgreso = recarga();
    }

    comportamiento();
}

void Habilidad::pausar() {
    relojDuracion.pausar();
    relojRecarga.pausar();
}

void Habilidad::reanudar() {
    relojDuracion.reanudar();
    relojRecarga.reanudar();
}