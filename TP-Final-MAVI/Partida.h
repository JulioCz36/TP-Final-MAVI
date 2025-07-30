#pragma once
#include <SFML/Graphics.hpp>

#include "Nave.h"

#include "Audio.h"

#include "Item.h"
#include "ItemBala.h"
#include "ItemVida.h"
#include "ItemPuntos.h"

#include "HUDPartida.h"
#include "Asteroide.h"

#include "Enemigo.h"
#include "DroneLigero.h"
#include "Caza.h"
#include "TorretaEspacial.h"

#include "Reloj.h"
#include "Figura.h"
#include "PausaMenu.h"

#include "Escenas.h"
#include "ImpactoVisual.h"
#include "Boss.h"
#include "Bala.h"

using namespace sf;
using namespace std;

class Partida : public Escena {

	// === FONDO EN MOVIMIENTO ===
	Figura fondo1, fondo2;
	float fondoVelocidad = 100.f;
	Reloj relojDeltaTime;

	shared_ptr<Audio>sonidoItem, sonidoImpacto, sonidoPartNormal;

	//=== Lasers de todos los objetos ===
	vector<unique_ptr<Bala>> lasersJugador;
	vector<unique_ptr<Bala>> lasersEnemigos; //Incluyendo al boss


	// === Asteroide ===
	vector<unique_ptr<Asteroide>> asteroides;
	Reloj relojGeneracion;
	float tiempoAsteroide = 1.5f;

	// === ÍTEMS, ENEMIGOS Y JUGADOR ===
	vector<unique_ptr<Item>> items;
	Reloj relojItem;
	String ultimo_item;

	// === ENEMIGO ===
	vector<unique_ptr<Enemigo>> enemigos;

	// ===JUGADOR ===
	Nave* jugador;

	vector <unique_ptr<ImpactoVisual>> impactos;
	vector<Texture> texturasImpacto;

	// === INTERFAZ DE USUARIO ===
	HUDPartida HUD;

	int enemigosAbatidos = 0;

	PausaMenu pausa;
	bool pausado = false;


	//==BOSS==
	unique_ptr<Boss> boss;
	bool bossAparecio = false;        // Si ya apareció completamente
	bool bossAnimandoEntrada = false;
	float tiempoAnimacionBoss = 5.f; 
	float bossTimer = 0.f;



	// === Manejo de Fondo ===
	void actualizarFondo(float deltaTime);


	// === Interaccion entre Objetos ===
	void asteroideYNave(float deltaTime);
	void enemigoYNave(float deltaTime);
	void itemYNave(float deltaTime);
	void bossYNave(float deltaTime);

	// === Generar Objetos ===
	void generarItems();
	void generarAsteroides();

public:
	Partida(RenderWindow& v,Nave* jugador);

	// === MÉTODOS PRINCIPALES ===
	void actualizar(Juego& j) override;
	void dibujar(RenderWindow& window) override;
	void procesoEventos(Juego& j, Event& event) override;

	void reanudar();
	void detenerSonido();
	void pausar();

	void agregarLasersJugador(unique_ptr<Bala> laser);
	void agregarLasersEnemigos(unique_ptr<Bala> laser);
	void limpiarBalas();
};

