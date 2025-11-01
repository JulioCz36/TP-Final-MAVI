#pragma once
#include <SFML/Graphics.hpp>
#include "Afichmation.h"
#include "Figura.h"
#include "utils.h"
#include "Nave.h"
#include "Audio.h"
using namespace sf;
using namespace std;

class Asteroide{
	Figura asteroide;
	Afichmation destruccion;
	shared_ptr<Audio>sonidoHit;

	// destrucción
	bool enDestruccion = false;
	bool fueraDePantalla = false;

	// configuración
	int velocidad;
	int vida = 1;
	int dano = 1;
	Vector2f direccion;
public:
	Asteroide(const string& texture, float speedMeteor, Vector2f dir, Vector2f pos);

	void dibujar(RenderTarget& window);
	void actualizar(float deltaTime, float posY);

	// interacción
	void recibirDano(float danoRecibido);
	float verDano() const;

	// destrucción
	void iniciarDestruccion();
	bool estaEnDestruccion() const;

	// colision y vida
	bool estaMuerto();
	bool colisionaCon(const FloatRect& objeto);

	// posición y bounds
	FloatRect verBounds();
	bool estaFueraDePantalla();
	Vector2f verPos();
};

