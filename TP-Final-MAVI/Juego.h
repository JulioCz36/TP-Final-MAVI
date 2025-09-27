#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include "utils.h"
#include "Escenas.h"
#include "Nave.h"


using namespace sf;
using namespace std;
class Escena;
class MenuPrincipal;

class Juego {
	RenderTexture renderTexture;
	Sprite renderSprite;

	RenderWindow w;
	Escena* actual;
	Escena* prox = nullptr;

	Nave* jugador = nullptr;

	bool debeReiniciar = false;

public:
	Juego();
	~Juego();

	void jugar();
	void actualizar();
	void dibujar();
	void cambiarScena(Escena* scena_nueva);
	void procesoEventos();

	void iniciarPartida();

	void reanudar();

	void marcarParaReiniciar();
	void reiniciar();
	void volverAlMenu();
	void  salir();
	void finDelJuego(int puntos);
};

