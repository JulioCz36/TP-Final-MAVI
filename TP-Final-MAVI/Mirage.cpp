#include "Mirage.h"

Mirage::Mirage() : Nave("assets/jugador/naves/mirage_sheet.png", 320.0f, 45) {
	habilidad = new Rapidez(3.0f, 1.0f);
}

void Mirage::habilidadNave() {
	habilidad->aplicarEfecto(*this);
}