#pragma once
#include <SFML/Graphics.hpp>
#include "Juego.h"
#include <SFML/Window/Event.hpp>
using namespace sf;
class Juego;

class Escena {
public:
	Escena() {};
	void virtual procesoEventos(Juego& j, Event& event) {}
	void virtual actualizar(Juego& j) = 0;
	void virtual dibujar(RenderTarget& target) = 0;
};
