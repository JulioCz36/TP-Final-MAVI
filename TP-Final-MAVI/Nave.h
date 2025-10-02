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
	Afichmation escudo;

	int vidaActual, vidaMaxima;

	// Movimiento vertical
	float velY = 0.f;
	float gravedad = 150.f;      // px/seg²
	float fuerzaSalto;  // px/seg (negativo porque sube)
	bool esperando = true;
	
	bool saltando = false;
	float alturaInicioCaida = 0.f;
	float limiteCaida = 500.f;   // metros antes de morir
	float alturaMaxAlcanzada = 0.f;

	// Variables de control 
	Keyboard::Key salto = Keyboard::Space;

	// Variables destrucción
	bool enDestruccion = false;

	// ----------------- Escudo -----------------
	bool escudoActivo = false;
	bool escudoDesactivandose = false;
	float duracionEscudo = 0.f;     
	Reloj relojEscudo;

	// Variables invulnerabilidad
	bool invulnerable = false;

	// ----------------- Propulsor Item -----------------
	bool propulsorActivo = false;
	float duracionPropulsor = 0.f;
	Reloj relojPropulsor;

	// Variables de control de Hurtbox y Hitbox
	Vector2f tam_central = { 0, 0 };
	Vector2f tam_superior = { 0, 0 };
	float offsetYSuperior = 0.f;

	float radioHitbox = 0.f;
	bool usarHitboxCircular = false;

	bool enPausa = false;

	void dibujarBox(RenderTarget& w);

public:
	Nave(float x, float y, float vel, int vida);

	// -----------------  MÉTODOS PRINCIPALES -----------------

	void actualizar(float deltaTime);
	void manejarEventos(Event& e);
	void dibujar(RenderTarget& w);

	// ----------------- Vida e invulnerabilidad -----------------

	void recibirDano(float dano);
	float verVida();
	float verVidaMax();
	void aumentarVida(int canVida);

	// ----------------- destrucción -----------------

	void iniciarDestruccion();
	bool estaEnDestruccion();
	bool estaMuerto();

	void activarEscudo(float segundos);
	bool estaConEscudo();
	void activarPropulsor(float segundos, float velocidadExtra);
	bool estaConPropulsor() ;

	bool colisionaCon(const FloatRect& otro);

	void pausar();
	void reanudar();

	void setPartida(Partida* p);

	Vector2f verPos();

	void iniciarSalto();
	void mantenerSalto();
	void finalizarSalto();
};

