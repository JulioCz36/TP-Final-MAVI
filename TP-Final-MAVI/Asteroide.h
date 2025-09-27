#pragma once
#include <SFML/Graphics.hpp>
#include "Afichmation.h"
using namespace sf;
using namespace std;

class Asteroide{
	// === REPRESENTACIÓN VISUAL ===
	Afichmation asteroide;
	static Texture texturaSheet;

	// === DESTRUCCIÓN Y ESTADO ===
	bool enDestruccion = false;

	bool fueraDePantalla = false;

	// === ESTADÍSTICAS ===
	int velocidad;
	int vida;
	int vidaMaxima;
	int dano;
public:
	Asteroide(const string& texture, int anchura, int altura,float speedAsteroide, float vidaAsteroide, float danoAsteroide);

	// ===  MÉTODOS PRINCIPALES ===
	void dibujar(RenderTarget& window);
	void actualizar(float deltaTime);

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
};

