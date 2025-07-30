#pragma once
#include <SFML/Graphics.hpp>
#include "Figura.h"
#include "Bala.h"
#include "Reloj.h"
#include "Afichmation.h"

#include "Nave.h"

using namespace sf;
using namespace std;

class Partida;

struct CirculoHitbox {
	Vector2f offset;
	float radio;
};

struct ParteBoss {
	unique_ptr<Figura> figura;
	bool destruido = false;
	string nombre; // "manoIzq", "manoDer", "canonIzq", "canonDer"

	ParteBoss(string n, const string& rutaImagen)
		: nombre(n)
	{
		figura = std::make_unique<Figura>();
		figura->cargarImagen(rutaImagen);
	}
};


enum class EstadoAtaqueManos {
	Esperando,
	Preparando,
	Disparando,
};


class Boss {
	Partida* partida = nullptr;

	Figura cuerpo;

	vector<ParteBoss> partesBoss;

	float vidaMaxima = 1000.f;    
	float vidaActual = 0.f;

	Vector2f cuerpoHibox;
	Vector2f brazo;
	vector<Vector2f> offsetHitboxesBrazo;
	CirculoHitbox hitboxCircularBrazoIzq, hitboxCircularBrazoDer;

	// Movimiento
	float velocidadX = 200.f;       // velocidad base 
	float limiteIzq = 473.5f;        // límite inicial izquierdo
	float limiteDer = 806.5f;      // límite inicial derecho

	bool yendoDerecha;      // dirección actual

	//Disparo de fuego
	EstadoAtaqueManos estadoManos = EstadoAtaqueManos::Esperando;
	float timerGeneral = 0;
	float timerAtaque = 20.f;
	float tiempoPreparando = 4.f;
	float tiempoEspera = 10.f;  
	vector<unique_ptr<Afichmation>> handBlasters;

	//Atributos para cañones
	Nave* jugador = nullptr;
	vector<Vector2f> pivotes =  { Vector2f(0.f, 0.f), Vector2f(0.f, 0.f) };
	vector<Vector2f> dirs = { Vector2f(0.f, 0.f), Vector2f(0.f, 0.f) };
	float angulo;
	int danio;
	float cadenciaDisparo = 1.5f;
	Reloj relojDisparo;


	void dibujarHitbox(RenderWindow& w);
	bool rectIntersectsCircle(const FloatRect& rect, const Vector2f& circleCenter, float circleRadius);

	void activarMovimientoCompleto(bool activo);
	void actualizarPartes();

public:
	Boss(const Nave* player, Partida* p);

	// ----------------- Vida e invulnerabilidad -----------------

	void recibirDano(float dano);
	void aumentarVida(int canVida);
	bool esInvulnerable();
	void activarInvulnerabilidad(float segundos);

	// ----------------- Disparo -----------------

	void disparar();
	bool puedeDisparar();

	//-------Atque manos-------
	void crearBlasters();
	void actualizarBlasters(float deltaTime);
	vector<unique_ptr<Afichmation>>& obtenerHandBlasters();

	// ----------------- Movimiento -----------------

	void moverEnX(float deltaTime);
	void quePositionY(float y);
	float verAltura();
	bool colisionaCon(const FloatRect& otro);


	// ----------------- Animación y estado visual -----------------

	void esVisible(bool visible);

	// -----------------  MÉTODOS PRINCIPALES -----------------

	void actualizar(float deltaTime);
	void dibujar(RenderWindow& w);
	// ----------------- Estado y destrucción -----------------

	void iniciarDestruccion();
	bool estaEnDestruccion();
	bool estaMuerto();

	float verVidaActual() { return vidaActual; }
	float verVidaMaxima() { return vidaMaxima; }
	// ----------------- Puntos -----------------

	void pausar();
	void reanudar();
};

