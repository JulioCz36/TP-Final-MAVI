#include "TorretaEspacial.h"

TorretaEspacial::TorretaEspacial(const Nave* player, Partida* p) : Enemigo(p,"assets/enemigos/torreta_sheet.png", 67, 98, { 0 }, { 0,1,2,3,4,5,6,7,8 }, {9},100.0f, 50, 1.5f, 3) {
	jugador = const_cast<Nave*>(player);
}

void TorretaEspacial::comportamiento(float deltaTime){
	Vector2f movimiento(0.0f, verVelocidad() * deltaTime);
	mover(movimiento);

	pivot = verPosition();

	dir = jugador->verPos() - pivot;
	angulo = atan2(dir.y, dir.x) * 180.f / 3.14f;
	queAngle(angulo - 90.f);
}

Vector2f TorretaEspacial::verDireccionDisparo() const {
	return dir;
}
