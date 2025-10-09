#include "Partida.h"

Partida::Partida(RenderWindow& v, Nave* player) :jugador(player), pausa(v), HUD(jugador->verVida()), UI(v,player){

	alturaReferencia = jugador->verPos().y;

	fondo1.cargarImagen("assets/Fondo/fondo.png");
	fondo2.cargarImagen("assets/Fondo/fondo.png");
	fondo1.quePosition(128 / 2, 256 / 2);
	fondo2.quePosition(128 / 2, fondo1.verPosition().y - fondo1.verGlobalBounds().height);

	fondoAdelante1.cargarImagen("assets/Fondo/fondo_arriba.png");
	fondoAdelante2.cargarImagen("assets/Fondo/fondo_arriba.png");
	fondoAdelante1.quePosition(128 / 2, 256 / 2);
	fondoAdelante2.quePosition(128 / 2, fondo1.verPosition().y - fondo1.verGlobalBounds().height);

	marte.cargarImagen("assets/Fondo/planeta_marte.png");
	marte.quePosition(128 / 2.f, alturaReferencia - DISTANCIA_A_MARTE);

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
		}if (jugador->estaMuerto()) {
			j.finDelJuego(false,static_cast<int>(alturaActual));
		}

		generarItems();
		itemYNave(deltaTime);

		generarAsteroides();
		asteroideYNave(deltaTime);

		alturaActual = alturaReferencia - jugador->verPos().y;
		if(alturaActual < 0) alturaActual = 0;

		if (alturaActual >= DISTANCIA_A_MARTE) {

			sonidoPartNormal->stop();
			j.finDelJuego(true,static_cast<int>(alturaActual));
		}

		jugador->actualizar(deltaTime);

		Vector2f center = camera.getCenter();
		
		if (jugador->verPos().y < 256.f / 2.f) {
			center.y = jugador->verPos().y;
			camera.setCenter(center);
		}
		UI.actualizar();
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

	if (marte.verPosition().y < camera.getCenter().y + camera.getSize().y / 2.f) {
		marte.dibujar(window);
	}

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
	UI.dibujar(window);
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
		if (e.type == Event::KeyPressed || e.type == Event::KeyReleased) {
			jugador->manejarEventos(e);
		}
		UI.manejarEventos(e);
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
		(*it)->actualizar(deltaTime, jugador->verPos().y);
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
		auto camaraY = camera.getCenter().y;
		float spawnY = camaraY - 280.f;
		float anchoPantalla = 128.f;

		bool desdeIzquierda = rand() % 2 == 0;
		bool esGrande = rand() % 2 == 0;
		float velocidad = 140.f + rand() % 60;

		bool hayCerca = false;
		for (const auto& a : asteroides) {
			float distanciaY = abs(a->verPos().y - spawnY);
			if (distanciaY < 40.f) { 
				hayCerca = true;
				break;
			}
		}

		if (!hayCerca) {
			string textura = esGrande
				? "assets/meteoritos/meteorito_grande.png"
				: "assets/meteoritos/meteorito_chico.png";

			if (desdeIzquierda) {
				asteroides.push_back(make_unique<Asteroide>(
					textura, velocidad,
					Vector2f(1.f, 0.f),
					Vector2f(-40.f, spawnY)
				));
			}
			else {
				asteroides.push_back(make_unique<Asteroide>(
					textura, velocidad,
					Vector2f(-1.f, 0.f),
					Vector2f(anchoPantalla + 40.f, spawnY)
				));
			}
		}

		relojGeneracion.reiniciar();
	}
}

void Partida::generarItems() {

	float intervalo = 5.f;

	if (relojItem.verTiempoTranscurrido() >= intervalo) {

		int random = rand() % 100;

		Vector2f spawnPos(jugador->verPos().x, jugador->verPos().y - 300.f);

		if (random < 20) {
			// 20%
			if (jugador->verVida() < jugador->verVidaMax()) {
				items.push_back(make_unique<ItemVida>(spawnPos));
			}
		}
		else if (random < 30) {
			// 10%
			if (!jugador->estaConPropulsor() && !jugador->estaConEscudo()) {
				items.push_back(make_unique<ItemPropulsor>(spawnPos));
			}
		}
		else if (random < 45) {
			// 15%
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

