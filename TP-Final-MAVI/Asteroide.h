#pragma once
#include <SFML/Graphics.hpp>
#include "Afichmation.h"
#include "Figura.h"
#include "utils.h"
#include "Nave.h"
using namespace sf;
using namespace std;

class Asteroide{
	// === REPRESENTACIÓN VISUAL ===
	Figura asteroide;
	Afichmation destruccion;

	// === DESTRUCCIÓN Y ESTADO ===
	bool enDestruccion = false;
	bool fueraDePantalla = false;

	// === ESTADÍSTICAS ===
	int velocidad;
	int vida = 1;
	int dano = 1;
	Vector2f direccion;
public:
	Asteroide(const string& texture, float speedMeteor, Vector2f dir, Vector2f pos);

	// ===  MÉTODOS PRINCIPALES ===
	void dibujar(RenderTarget& window);
	void actualizar(float deltaTime, float posY);

	// === INTERACCIÓN ===
	void recibirDano(float danoRecibido);
	float verDano() const;

	// === DESTRUCCIÓN ===
	void iniciarDestruccion();
	bool estaEnDestruccion() const;

	// === COLISIÓN Y VIDA ===
	bool estaMuerto();
	bool colisionaCon(const FloatRect& objeto);

	// === POSICIÓN Y BOUNDS ===
	FloatRect verBounds();
	bool estaFueraDePantalla();
	Vector2f verPos();
};

