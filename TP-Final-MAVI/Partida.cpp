#include "Partida.h"

Partida::Partida(RenderWindow& v, Nave* player) :jugador(player), pausa(v), HUD(jugador->verVida()){

	alturaReferencia = jugador->verPos().y;

	fondo1.cargarImagen("assets/Fondo/fondo.png");
	fondo2.cargarImagen("assets/Fondo/fondo.png");
	fondo1.quePosition(128 / 2, 256 / 2);
	fondo2.quePosition(128 / 2, fondo1.verPosition().y - fondo1.verGlobalBounds().height);

	fondoAdelante1.cargarImagen("assets/Fondo/fondo_arriba.png");
	fondoAdelante2.cargarImagen("assets/Fondo/fondo_arriba.png");
	fondoAdelante1.quePosition(128 / 2, 256 / 2);
	fondoAdelante2.quePosition(128 / 2, fondo1.verPosition().y - fondo1.verGlobalBounds().height);

	relojGeneracion.reiniciar();


	sonidoPartNormal = make_shared<Audio>();

	sonidoPartNormal->cargar("assets/sonidos/sonido_batalla_normal.wav");
	sonidoPartNormal->queVolumen(25);

	camera.reset(FloatRect(0, 0, 128, 256));
}

void Partida::actualizar(Juego& j) {

	float deltaTime = 0.f;
	if (!pausado) {
		if (!sonidoPartNormal->estaReproduciendo()) {
			sonidoPartNormal->play();
		}
		deltaTime = relojDeltaTime.verReinicio();

		actualizarFondo();

		if (jugador->estaEnDestruccion()) {
			sonidoPartNormal->stop();
			//musica derrota->play();
		}if (jugador->estaMuerto()) {
			j.finDelJuego(static_cast<int>(alturaActual));
		}

		generarItems();
		itemYNave(deltaTime);
		//generarAsteroides();
 
		//asteroideYNave(deltaTime);

		alturaActual = alturaReferencia - jugador->verPos().y;
		if(alturaActual < 0) alturaActual = 0;
		jugador->actualizar(deltaTime);

		Vector2f center = camera.getCenter();
		
		if (jugador->verPos().y < 256.f / 2.f) {
			center.y = jugador->verPos().y;
			camera.setCenter(center);
		}

		HUD.actualizar(jugador->verVida(), static_cast<int>(alturaActual));

	}else {
		if (sonidoPartNormal->estaReproduciendo()) {
			sonidoPartNormal->pausa();
		}
		relojDeltaTime.reiniciar();
		pausa.actualizarMenu();
	}

}
void Partida::dibujar(RenderTarget& window) {
	window.setView(camera);

	fondo1.dibujar(window);
	fondo2.dibujar(window);

	jugador->dibujar(window);

	for (auto& meteor : asteroides) {
		meteor->dibujar(window);
	}
	for (auto it = items.begin(); it != items.end(); ++it) {
		(*it)->dibujar(window);
	}

	fondoAdelante1.dibujar(window);
	fondoAdelante2.dibujar(window);

	window.setView(window.getDefaultView());
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

void Partida::actualizarFondo() {
	float altura = fondo1.verGlobalBounds().height;

	float camY = camera.getCenter().y; 
	float mitadAlturaVista = camera.getSize().y / 2.f;

	// Aca lo que hago es ir moviendo los fondos hacia arriba
	if (fondo1.verPosition().y - altura / 2.f > camY + mitadAlturaVista) {
		fondo1.quePosition(fondo1.verPosition().x, fondo2.verPosition().y - altura);
		fondoAdelante1.quePosition(fondo1.verPosition().x, fondo2.verPosition().y - altura);
	}
	if (fondo2.verPosition().y - altura / 2.f > camY + mitadAlturaVista) {
		fondo2.quePosition(fondo2.verPosition().x, fondo1.verPosition().y - altura);
		fondoAdelante2.quePosition(fondo2.verPosition().x, fondo1.verPosition().y - altura);
	}

	// Aca lo que hago es ir moviendo los fondos hacia abajo
	if (fondo1.verPosition().y + altura / 2.f < camY - mitadAlturaVista) {
		fondo1.quePosition(fondo1.verPosition().x, fondo2.verPosition().y + altura);
		fondoAdelante1.quePosition(fondo1.verPosition().x, fondo2.verPosition().y + altura);
	}

	if (fondo2.verPosition().y + altura / 2.f < camY - mitadAlturaVista) {
		fondo2.quePosition(fondo2.verPosition().x, fondo1.verPosition().y + altura);
		fondoAdelante2.quePosition(fondo2.verPosition().x, fondo1.verPosition().y + altura);
	}
}

void Partida::asteroideYNave(float deltaTime) {
	for (auto it = asteroides.begin(); it != asteroides.end(); ) {
		(*it)->actualizar(deltaTime);
		++it;
	}

	for (auto it = asteroides.begin(); it != asteroides.end();) {

		if (jugador->colisionaCon((*it)->verBounds()) && !(*it)->estaEnDestruccion()) {
			jugador->recibirDano((*it)->verDano());
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
void Partida::generarAsteroides() {
	if (relojGeneracion.verTiempoTranscurrido() >= tiempoAsteroide) {
		int prob = rand() % 100;

		if (prob < 60) {
			asteroides.push_back(make_unique<Asteroide>("assets/partida/asteroides/asteroide_chico_sheet.png", 28, 28, 100, 20, 5));
		}
		else if (prob < 90) {
			asteroides.push_back(make_unique<Asteroide>("assets/partida/asteroides/asteroide_mediano_sheet.png", 43, 43, 75, 30, 10));
		}
		else {
			asteroides.push_back(make_unique<Asteroide>("assets/partida/asteroides/asteroide_grande_sheet.png", 89, 82, 50, 45, 20));
		}

		relojGeneracion.reiniciar();
	}
}

void Partida::generarItems() {

	float intervalo = 3.f;

	if (relojItem.verTiempoTranscurrido() >= intervalo) {

		int random = rand() % 100;

		Vector2f spawnPos(jugador->verPos().x, jugador->verPos().y - 300.f);

		if (random < 35) {
			// 35%
			if (jugador->verVida() < jugador->verVidaMax()) {
				items.push_back(make_unique<ItemVida>(spawnPos));
			}
		}
		else if (random < 55) {
			// 20%
			if (!jugador->estaConPropulsor() && !jugador->estaConEscudo()) {
				items.push_back(make_unique<ItemPropulsor>(spawnPos));
			}
		}
		else if (random < 80) {
			// 25%
			if (!jugador->estaConEscudo() && !jugador->estaConPropulsor()) {
				items.push_back(make_unique<ItemEscudo>(spawnPos));
			}
		}

		relojItem.reiniciar();
	}
}
void Partida::itemYNave(float deltaTime) {
	for (auto it = items.begin(); it != items.end(); ) {
		(*it)->actualizar(deltaTime);

		if ((*it)->estaTerminado()) {
			it = items.erase(it);
		}
		else if (!(*it)->estaTerminado() && jugador->colisionaCon((*it)->verBounds())) {
			(*it)->recoger(*jugador);
			++it;
		}
		else {
			++it;
		}
	}
}

float Partida::verAlturaReferencia() { return alturaReferencia; }
float Partida::verAlturaActual() { return alturaActual; }

