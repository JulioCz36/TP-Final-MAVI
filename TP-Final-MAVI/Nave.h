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

	shared_ptr<Audio>sonidoImpacto, sonidoPropulsor, sonidoEscudo;

	int vidaActual, vidaMaxima;

	// Movimiento vertical
	float velY = 0.f;
	float gravedad = 300.f;      // px/seg²
	float fuerzaSalto;  // px/seg (negativo porque sube)
	bool esperando = true;
	
	bool saltando = false;
	float alturaInicioCaida = 0.f;
	float limiteCaida = 500.f;   // metros antes de morir
	float alturaMaxAlcanzada = 0.f;

	//Animación hit
	bool enDanio = false;
	Reloj relojDanio;
	float duracionDanio = 0.8f; 
	float intervaloDanio = 0.1f;

	// control 
	Keyboard::Key salto = Keyboard::Space;

	// Escudo 
	bool escudoActivo = false;
	bool escudoDesactivandose = false;
	float duracionEscudo = 0.f;     
	Reloj relojEscudo;

	// invulnerabilidad
	bool invulnerable = false;
	
	// destrucción
	bool enDestruccion = false;

	// item propulsor
	bool propulsorActivo = false;
	float duracionPropulsor = 0.f;
	Reloj relojPropulsor;

	// control de Hurtbox y Hitbox
	Vector2f tam_central = { 0, 0 };
	Vector2f tam_superior = { 0, 0 };
	float offsetYSuperior = 0.f;

	float radioHitbox = 0.f;
	bool usarHitboxCircular = false;

	bool enPausa = false;

	void dibujarBox(RenderTarget& w);

public:
	Nave(float x, float y, float vel, int vida);

	// MÉTODOS PRINCIPALES

	void actualizar(float deltaTime);
	void manejarEventos(Event& e);
	void dibujar(RenderTarget& w);

	// Vida

	void recibirDano(float dano);
	float verVida();
	float verVidaMax();
	void aumentarVida(int canVida);

	// destrucción

	void iniciarDestruccion();
	bool estaEnDestruccion();
	bool estaMuerto();


	// Items
	void activarEscudo(float segundos);
	bool estaConEscudo();
	void activarPropulsor(float segundos, float velocidadExtra);
	bool estaConPropulsor() ;

	// otros
	bool colisionaCon(const FloatRect& otro);

	void pausar();
	void reanudar();

	void setPartida(Partida* p);

	Vector2f verPos();

	void iniciarSalto();
	void mantenerSalto();
	void finalizarSalto();
};

