#pragma once
#include <SFML/Graphics.hpp>
#include "Afichmation.h"
#include "Figura.h"
#include "utils.h"
#include "Nave.h"
using namespace sf;
using namespace std;

class Asteroide{
	// === REPRESENTACI�N VISUAL ===
	Figura asteroide;
	Afichmation destruccion;

	// === DESTRUCCI�N Y ESTADO ===
	bool enDestruccion = false;
	bool fueraDePantalla = false;

	// === ESTAD�STICAS ===
	int velocidad;
	int vida = 1;
	int dano = 1;
	Vector2f direccion;
public:
	Asteroide(const string& texture, float speedMeteor, Vector2f dir, Vector2f pos);

	// ===  M�TODOS PRINCIPALES ===
	void dibujar(RenderTarget& window);
	void actualizar(float deltaTime, float posY);

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
	Vector2f verPos();
};

