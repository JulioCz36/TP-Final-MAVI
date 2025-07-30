#pragma once
#include <SFML/Graphics.hpp>
#include "Item.h"
#include "Habilidad.h"
#include "Reloj.h"
#include "Figura.h"
#include "Afichmation.h"
#include "Audio.h"
#include "Bala.h"
class Item;
class Habilidad;
class Partida;

using namespace sf;
using namespace std;


class Nave {
protected:

	Habilidad* habilidad;
private:

	Partida* partida = nullptr;


	// Parámetros de animación
	Afichmation nave;
	Afichmation fire;

	Audio sonidoDisparo;


	// Control de destrucción
	bool enDestruccion = false;
	float tiempoDestruccion = 0.3f;
	int repeticionesDestruccion = 0;


	// Variables de control y movimiento
	Keyboard::Key acel = Keyboard::W;
	Keyboard::Key retro = Keyboard::S;
	Keyboard::Key izq = Keyboard::A;
	Keyboard::Key der = Keyboard::D;
	Keyboard::Key dis = Keyboard::J;
	bool puedeDisparar = true;
	Keyboard::Key habi = Keyboard::K;

	int velocidad, resistencia, resistenciaMaxima, balasEspeciales;
	int bala_n = 2;
	int puntos = 0;

	// Disparo
	bool dobleDisparoActivo = false;

	// Variables invulnerabilidad
	bool invulnerable = false;
	float duracionInvulnerabilidad;
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
	Nave(const string& texture, int vel, int resi);

	// ----------------- Vida e invulnerabilidad -----------------

	void recibirDano(float dano);
	float verVida();
	void aumentarVida(int canVida);
	bool esInvulnerable();
	void activarInvulnerabilidad(float segundos);

	// ----------------- Habilidades -----------------

	virtual void habilidadNave() = 0;
	Habilidad* queHabilidad();

	// ----------------- Disparo -----------------

	void disparar();
	void cambiarBalas(int n_bullet, int cantidad);
	int verCanBalas();

	// Doble disparo
	void doubleBalaSi(int cantidad);
	void doubleBalaNo();

	// ----------------- Movimiento -----------------

	void mover(float deltaTime);
	void cambiarPos(float desplazamiento);
	Vector2f verPos();
	bool estaQuieto();

	void configurarHitboxCircular(float radio, float offsetY);
	void hitboxCircular(bool activar);
	bool colisionaCon(const FloatRect& otro);
	void dibujarHitbox(RenderWindow& w);
	void verificarLimitesPantalla();
	

	// ----------------- Animación y estado visual -----------------

	void actualizarAvance(bool avanzando);
	void esVisible(bool visible);

	// -----------------  MÉTODOS PRINCIPALES -----------------

	void actualizar(float deltaTime);
	void manejarEventos(Event& e);
	void dibujar(RenderWindow& w);

	// ----------------- Estado y destrucción -----------------

	void iniciarDestruccion();
	bool estaEnDestruccion();
	bool estaMuerto();

	// ----------------- Puntos -----------------

	void aumentarPuntos(int canPuntos);
	int verPuntos();

	void pausar();
	void reanudar();

	void setPartida(Partida* p);

};

