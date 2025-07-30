#include "Onyx.h"

Onyx::Onyx() :Nave("assets/jugador/naves/onyx_sheet.png", 220.0f, 70) {
	habilidad = new Escudo(4.0f, 6.0f);
	configurarHitboxCircular(66,10);
}

void Onyx::habilidadNave() {
	habilidad->aplicarEfecto(*this);
}

