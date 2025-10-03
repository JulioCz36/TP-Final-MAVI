#include "Juego.h"
#include "Partida.h"
#include "FinDelJuego.h"
#include "MenuPrincipal.h"
#include "PausaMenu.h"
#include "Instrucciones.h"

Juego::Juego() : w(VideoMode::getDesktopMode(), "Mars Express", Style::Fullscreen) {
	w.setFramerateLimit(60);

	renderTexture.create(128, 256);
	renderSprite.setTexture(renderTexture.getTexture());

	auto screenSize = w.getSize();
	float scaleX = static_cast<float>(screenSize.x) / 128.f;
	float scaleY = static_cast<float>(screenSize.y) / 256.f;

	float scale = std::min(scaleX, scaleY);

	renderSprite.setScale(scale, scale);

	float offsetX = (screenSize.x - 128.f * scale) / 2.f;
	float offsetY = (screenSize.y - 256.f * scale) / 2.f;
	renderSprite.setPosition(offsetX, offsetY);

	//actual = new MenuPrincipal(w);
	actual = new Instrucciones(w);
}
Juego::~Juego() {
	delete actual;
	delete jugador;
}
void Juego::jugar() {

	while (w.isOpen()) {
		procesoEventos();
		dibujar();
		actualizar();

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
void Juego::dibujar() {
	renderTexture.clear();
	actual->dibujar(renderTexture);
	renderTexture.display();

	w.clear();
	w.draw(renderSprite);

	RectangleShape marco(Vector2f(renderSprite.getGlobalBounds().width, renderSprite.getGlobalBounds().height));
	marco.setFillColor(Color::Transparent);
	marco.setOutlineColor(Color::Red);
	marco.setOutlineThickness(3.f);
	marco.setPosition(renderSprite.getPosition());
	w.draw(marco);

	w.display();
}


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

void Juego::iniciarPartida() {
	jugador = new Nave(128/2,190,140, 3);
	auto nuevaPartida = new Partida(w, jugador);
	jugador->setPartida(nuevaPartida);
	cambiarScena(nuevaPartida);
}

void Juego::reanudar() {
	if (auto partida = dynamic_cast<Partida*>(actual)) {
		partida->reanudar();
	}
}
void Juego::reiniciar() {
	if (auto partida = dynamic_cast<Partida*>(actual)) {
		partida->detenerSonido();
	}

	delete jugador;
	jugador = nullptr;
	iniciarPartida();
}
void Juego::volverAlMenu() {
	cambiarScena(new MenuPrincipal(w));
}

void Juego::verInstrucciones() {
	cambiarScena(new Instrucciones(w));
}
void Juego::salir() {w.close();}

void Juego::finDelJuego(int metros){
	cambiarScena(new FinDelJuego(w, metros));
}
