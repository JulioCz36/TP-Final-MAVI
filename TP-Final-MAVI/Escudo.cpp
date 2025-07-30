#include "Escudo.h"

Escudo::Escudo(float tiempoRecarga, float duracion) : Habilidad(tiempoRecarga, duracion) {
    spriteEscudo.cargarImagen("assets/jugador/habilidades/escudo.png");
}

void Escudo::aplicarEfecto(Nave& nave) {
    if (relojRecarga.verTiempoTranscurrido() >= tiempoRecarga) {
        activa = true;
        relojDuracion.reiniciar();
        naveRef = &nave;

        naveRef->activarInvulnerabilidad(duracion);
        naveRef->hitboxCircular(true);
    }
}
void Escudo::comportamiento() {
    if(!activa && naveRef){
        naveRef->hitboxCircular(false);
    }
}

string Escudo::verRutaTextura() {
    return "assets/jugador/habilidades/escudo_sheet.png";
}
void Escudo::dibujar(RenderWindow& w) {
    if (activa && naveRef) {
        spriteEscudo.quePosition(naveRef->verPos().x, naveRef->verPos().y); 
        spriteEscudo.dibujar(w);
    }
}