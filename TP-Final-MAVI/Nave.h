#pragma once
#include <SFML/Graphics.hpp>
#include "Item.h"
#include "Reloj.h"
#include "Figura.h"
#include "Afichmation.h"
#include "Audio.h"
class Item;
class Partida;

using namespace sf;
using namespace std;


class Nave {

	Partida* partida = nullptr;
	Figura nave;
	Afichmation destruccion;
	Afichmation propulsor;

	// Movimiento vertical
	float velY = 0.f;
	float gravedad = 200.f;      // px/seg²
	float fuerzaSalto;  // px/seg (negativo porque sube)
	bool esperando = true;
	
	bool saltando = false;
	float alturaInicioCaida = 0.f;
	float limiteCaida = 100.f;   // “metros” antes de morir

	bool enDestruccion = false;
	float tiempoDestruccion = 0.3f;
	int repeticionesDestruccion = 0;

	// Variables de control y movimiento
	Keyboard::Key salto = Keyboard::Space;

	int resistencia, resistenciaMaxima;

	// Variables invulnerabilidad
	bool invulnerable = false;
	float duracionInvulnerabilidad = 0;
	Reloj relojInvulnerabilidad;

	// Contenedores de elementos

	bool enPausa = false;

	Vector2f tam_central = { 0, 0 };
	Vector2f tam_superior = { 0, 0 };
	float offsetYSuperior = 0.f;

	float radioHitbox = 0.f;
	float offsetYHitboxCircular = 0.f;
	bool usarHitboxCircular = false;


public:
	Nave(float x, float y, float vel, int resi);

	// ----------------- Vida e invulnerabilidad -----------------

	void recibirDano(float dano);
	float verVida();
	void aumentarVida(int canVida);
	bool esInvulnerable();
	void activarInvulnerabilidad(float segundos);

	// ----------------- Movimiento -----------------
	Vector2f verPos();
	bool estaQuieto();


	bool colisionaCon(const FloatRect& otro);
	void dibujarHitbox(RenderWindow& w);
	void verificarLimitesPantalla();

	// -----------------  MÉTODOS PRINCIPALES -----------------

	void actualizar(float deltaTime);
	void manejarEventos(Event& e);
	void dibujar(RenderTarget& w);

	// ----------------- Estado y destrucción -----------------

	void iniciarDestruccion();
	bool estaEnDestruccion();
	bool estaMuerto();


	void pausar();
	void reanudar();

	void configurarHitboxCircular(float radio, float offsetY);

	void hitboxCircular(bool activar);

	void setPartida(Partida* p);

};

