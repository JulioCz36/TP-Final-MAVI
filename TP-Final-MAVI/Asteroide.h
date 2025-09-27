#pragma once
#include <SFML/Graphics.hpp>
#include "Afichmation.h"
using namespace sf;
using namespace std;

class Asteroide{
	// === REPRESENTACI�N VISUAL ===
	Afichmation asteroide;
	static Texture texturaSheet;

	// === DESTRUCCI�N Y ESTADO ===
	bool enDestruccion = false;

	bool fueraDePantalla = false;

	// === ESTAD�STICAS ===
	int velocidad;
	int vida;
	int vidaMaxima;
	int dano;
public:
	Asteroide(const string& texture, int anchura, int altura,float speedAsteroide, float vidaAsteroide, float danoAsteroide);

	// ===  M�TODOS PRINCIPALES ===
	void dibujar(RenderTarget& window);
	void actualizar(float deltaTime);

	// === INTERACCI�N ===
	void recibirDano(float danoRecibido);
	float verDano() const;

	// === DESTRUCCI�N ===
	void iniciarDestruccion();
	bool estaEnDestruccion() const;

	// === COLISI�N Y VIDA ===
	bool estaMuerto();
	bool colisionaCon(const FloatRect& objeto);

	// === POSICI�N Y BOUNDS ===
	FloatRect verBounds();
	bool estaFueraDePantalla();
};

