#include "Juego.h"
#include "Partida.h"
#include "ElegirNave.h"
#include "FinDelJuego.h"
#include "MenuPrincipal.h"
#include "PausaMenu.h"

Juego::Juego() : w(VideoMode(1280, 720), "Star Assault", Style::Titlebar | Style::Close) {
	w.setFramerateLimit(60);
	actual = new MenuPrincipal(w);

}
Juego::~Juego() {
	delete actual;
	delete jugador;
}
void Juego::jugar() {

	while (w.isOpen()) {
		procesoEventos();
		w.clear();

		actualizar();

		dibujar();


		w.display();

		if (prox) {
			delete actual;
			actual = prox;
			prox = nullptr;
		}

	}
}

void Juego::actualizar() {
	actual->actualizar(*this);

	//esto agregue para reiniciar partida en el menu pausa
	if (debeReiniciar) {
		debeReiniciar = false;
		reiniciar();
	}
	if (prox) {
		delete actual;
		actual = prox;
		prox = nullptr;
	}
}
void Juego::dibujar() {actual->dibujar(w);}

void Juego::procesoEventos() {
	Event e;
	while (w.pollEvent(e)) {
		if (e.type == Event::Closed) {
			w.close();
		}
		else {
			actual->procesoEventos(*this, e);
		}
	}
}

void Juego::cambiarScena(Escena* scena_nueva) {
	prox = scena_nueva;
}

void Juego::queTipoNaveElegido(TipoNave tipo) {
	tipoSeleccionado = tipo;
	switch (tipo) {
	case ONYX:
		jugador = new Onyx();
		break;
	case MIRAGE:
		jugador = new Mirage();
		break;
	}
}

void Juego::iniciarPartida() {
	auto nuevaPartida = new Partida(w, jugador);
	jugador->setPartida(nuevaPartida);
	cambiarScena(nuevaPartida);
}

void Juego::reanudar() {
	if (auto partida = dynamic_cast<Partida*>(actual)) {
		partida->reanudar();
	}
}
void Juego::marcarParaReiniciar() {
	debeReiniciar = true;
}
void Juego::reiniciar() {
	if (auto partida = dynamic_cast<Partida*>(actual)) {
		partida->detenerSonido();
	}

	delete jugador;
	jugador = nullptr;
	queTipoNaveElegido(tipoSeleccionado);
	iniciarPartida();
}
void Juego::cambiarNave() {
	cambiarScena(new ElegirNave(w));
}
void Juego::volverAlMenu() {
	cambiarScena(new MenuPrincipal(w));
}
void Juego::salir() {w.close();}

void Juego::finDelJuego(int enemigos,int puntos){
	cambiarScena(new FinDelJuego(w,enemigos,puntos));
}
