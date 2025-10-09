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
	Escena* escenaAnterior = nullptr;
	bool noBorrarActual = false;

	Nave* jugador = nullptr;

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

	void reiniciar();
	void volverAlMenu();
	void verInstrucciones();
	void comenzar();
	void irAAjustes();
	void salirDeAjustes();
	void  salir();
	void finDelJuego(bool resultado, int metros);
};

