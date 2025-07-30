#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include "utils.h"
#include "Escenas.h"
#include "Nave.h"
#include "Mirage.h"
#include "Onyx.h"


using namespace sf;
using namespace std;
class Escena;
class MenuPrincipal;

class Juego {
	RenderWindow w;
	Escena* actual;
	Escena* prox = nullptr;

	Nave* jugador = nullptr;
	TipoNave tipoSeleccionado = MIRAGE;

	bool debeReiniciar = false;

public:
	Juego();
	~Juego();

	void jugar();
	void actualizar();
	void dibujar();
	void cambiarScena(Escena* scena_nueva);
	void procesoEventos();

	void queTipoNaveElegido(TipoNave tipo);

	void iniciarPartida();

	void reanudar();

	void marcarParaReiniciar();
	void reiniciar();
	void cambiarNave();
	void volverAlMenu();
	void  salir();
	void finDelJuego(int enemigos, int puntos);
};

