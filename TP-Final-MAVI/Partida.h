#pragma once
#include <SFML/Graphics.hpp>

#include "Nave.h"

#include "Audio.h"

#include "Item.h"
#include "ItemVida.h"

#include "HUDPartida.h"
#include "Asteroide.h"

#include "Reloj.h"
#include "Figura.h"
#include "PausaMenu.h"

#include "Escenas.h"

using namespace sf;
using namespace std;

class Partida : public Escena {

	View camera;

	// === FONDO EN MOVIMIENTO ===
	Figura fondo1, fondo2;
	float fondoVelocidad = 100.f;
	Reloj relojDeltaTime;

	shared_ptr<Audio>sonidoItem, sonidoPartNormal;


	// === Asteroide ===
	vector<unique_ptr<Asteroide>> asteroides;
	Reloj relojGeneracion;
	float tiempoAsteroide = 1.5f;

	// === ÍTEMS,Y JUGADOR ===
	vector<unique_ptr<Item>> items;
	Reloj relojItem;
	String ultimo_item;

	// ===JUGADOR ===
	Nave* jugador;

	// === INTERFAZ DE USUARIO ===
	HUDPartida HUD;

	PausaMenu pausa;
	bool pausado = false;

	// === Manejo de Fondo ===
	void actualizarFondo(float deltaTime);


	// === Interaccion entre Objetos ===
	void asteroideYNave(float deltaTime);
	void itemYNave(float deltaTime);

	// === Generar Objetos ===
	void generarItems();
	void generarAsteroides();

public:
	Partida(RenderWindow& v,Nave* jugador);

	// === MÉTODOS PRINCIPALES ===
	void actualizar(Juego& j) override;
	void dibujar(RenderTarget& window) override;
	void procesoEventos(Juego& j, Event& event) override;

	void reanudar();
	void detenerSonido();
	void pausar();
};

