#include "Partida.h"

Partida::Partida(RenderWindow& v, Nave* player) :jugador(player), pausa(v), HUD(3){

	fondo1.cargarImagen("assets/Fondo/fondo.png");
	fondo2.cargarImagen("assets/Fondo/fondo.png");

	fondo1.quePosition(128 / 2, 256 / 2);
	fondo2.quePosition(128 / 2, fondo1.verPosition().y - fondo1.verGlobalBounds().height);

	relojGeneracion.reiniciar();

	sonidoItem = make_shared<Audio>();
	sonidoPartNormal = make_shared<Audio>();

	sonidoItem->cargar("assets/sonidos/item_up.wav");
	sonidoItem->queVolumen(50);
	sonidoPartNormal->cargar("assets/sonidos/sonido_batalla_normal.wav");
	sonidoPartNormal->queVolumen(25);

	camera.reset(sf::FloatRect(0, 0, 128, 256));
}

void Partida::actualizar(Juego& j) {

	float deltaTime = 0.f;
	if (!pausado) {
		if (!sonidoPartNormal->estaReproduciendo()) {
			sonidoPartNormal->play();
		}
		deltaTime = relojDeltaTime.verReinicio();

		actualizarFondo(deltaTime);

		if (jugador->estaMuerto()) {
			sonidoPartNormal->stop();
			//j.finDelJuego(jugador->verPuntos());
			return;
		}

		//generarItems();
		//egenerarAsteroides();

		asteroideYNave(deltaTime);
		itemYNave(deltaTime);

		jugador->actualizar(deltaTime);
		camera.setCenter(jugador->verPos());

		HUD.actualizar(3, 20);

	}else {
		if (sonidoPartNormal->estaReproduciendo()) {
			sonidoPartNormal->pausa();
		}
		relojDeltaTime.reiniciar();
		pausa.actualizarMenu();
	}

}
void Partida::dibujar(RenderTarget& window) {
	RenderWindow* rw = dynamic_cast<RenderWindow*>(&window);
	rw->setView(rw->getDefaultView());

	fondo1.dibujar(window);
	fondo2.dibujar(window);

	rw->setView(camera);

	jugador->dibujar(window);

	for (auto& meteor : asteroides) {
		meteor->dibujar(window);
	}
	for (auto it = items.begin(); it != items.end(); ++it) {
		(*it)->dibujar(window);
	}

	rw->setView(rw->getDefaultView());
	HUD.dibujar(window);

	if (pausado) {
		pausa.dibujarMenu(window);
	}
}
void Partida::procesoEventos(Juego& j, Event& e) {
	if (pausado) {
		pausa.procesoEventosMenu(j,e);
		if (pausa.verAccion() != Opciones::Ninguna) return;
	}
	else {
		if (e.type == Event::KeyPressed && e.key.code == Keyboard::Escape) {
			pausar();
		}
		jugador->manejarEventos(e);
	}
}

void Partida::reanudar() {
	pausado = false;
	relojDeltaTime.reanudar();
	relojGeneracion.reanudar();
	relojItem.reanudar();
	jugador->reanudar();
	pausa.resetearAccion();
}
void Partida::detenerSonido() {
	if (sonidoPartNormal) {
		sonidoPartNormal->stop();
	}
}
void Partida::pausar() {
	pausado = true;
	relojDeltaTime.pausar();
	relojGeneracion.pausar();
	relojItem.pausar();
	jugador->pausar();
}

void Partida::actualizarFondo(float deltaTime) {
	float altura = fondo1.verGlobalBounds().height;

	fondo1.mover(0, fondoVelocidad * deltaTime);
	fondo2.mover(0, fondoVelocidad * deltaTime);

	float borde1 = fondo1.verPosition().y + altura / 2.f;
	float borde2 = fondo2.verPosition().y + altura / 2.f;

	if (borde1 >= 256 * 2) {
		fondo1.quePosition(fondo1.verPosition().x, fondo2.verPosition().y - altura);
	}
	if (borde2 >= 256 * 2) {
		fondo2.quePosition(fondo2.verPosition().x, fondo1.verPosition().y - altura);
	}
}

void Partida::asteroideYNave(float deltaTime) {
	for (auto it = asteroides.begin(); it != asteroides.end(); ) {
		(*it)->actualizar(deltaTime);
		++it;
	}

	for (auto it = asteroides.begin(); it != asteroides.end();) {

		if (jugador->colisionaCon((*it)->verBounds()) && !(*it)->estaEnDestruccion()) {
			if (!jugador->esInvulnerable()) {
				jugador->recibirDano((*it)->verDano());
			}
			(*it)->iniciarDestruccion();
			++it;
			continue;
		}


		if ((*it)->estaMuerto() || (*it)->estaFueraDePantalla()) {
			it = asteroides.erase(it);
		}
		else {
			++it;
		}
	}
}

void Partida::itemYNave(float deltaTime) {
	for (auto it = items.begin(); it != items.end(); ) {
		(*it)->actualizar(deltaTime);
		if ((*it)->fueraDePantalla()) {
			it = items.erase(it);
		}
		else {
			++it;
		}
	}
	for (auto it = items.begin(); it != items.end(); ) {
		if (jugador->colisionaCon((*it)->verBounds())) {

			sonidoItem->play();

			(*it)->aplicarEfecto(*jugador);

			if ((*it)->mostrarEnHUD()) {
				ultimo_item = (*it)->verItem();
			}
			it = items.erase(it);
		}
		else {
			++it;
		}
	}
}

void Partida::generarItems() {
	float intervalo = 3.5f;

	if (relojItem.verTiempoTranscurrido() >= intervalo) {
		int random = rand() % 100;

		if (random < 30) {
			// 0–29 → Item_puntos

		}
		else if (random < 50) {
			// 30–49 → Item_rapida
		}
		else if (random < 65) {
			// 50–64 → Item_doble
		}
		else if (random < 80) {
			// 65–79 → Item_pesada
		}
		else if (random < 90) {
			// 80–89 → Item_bomba
		}
		else {
			// 90–99 → Item_vida
			items.push_back(make_unique<ItemVida>());
		}

		relojItem.reiniciar();
	}
}
void Partida::generarAsteroides() {
	if (relojGeneracion.verTiempoTranscurrido() >= tiempoAsteroide) {
		int prob = rand() % 100;

		if (prob < 60) {
			asteroides.push_back(make_unique<Asteroide>("assets/partida/asteroides/asteroide_chico_sheet.png",28,28,100, 20, 5));
		}else if (prob < 90) {
			asteroides.push_back(make_unique<Asteroide>("assets/partida/asteroides/asteroide_mediano_sheet.png", 43, 43, 75, 30, 10));
		}else {
			asteroides.push_back(make_unique<Asteroide>("assets/partida/asteroides/asteroide_grande_sheet.png", 89, 82, 50, 45, 20));
		}

		relojGeneracion.reiniciar();
	}
}
