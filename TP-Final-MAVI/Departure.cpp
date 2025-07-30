#include "Departure.h"
#include "ShipN2.h"
#include "FinDelJuego.h"
Departure::Departure(Ship* jugador) : player(jugador), UI(player->queSkill()) {
	fondo1.cargarSprite("assets/departure/fondo.png");
	fondo2.cargarSprite("assets/departure/fondo.png");

	fondo1.setPosition(400, 0);
	fondo2.setPosition(400, fondo1.getPosition().y - fondo1.getGlobalBounds().height);

	relojGeneracion.reiniciar();

	enemigos.push_back(make_unique<DroneLigero>());
	enemigos.push_back(make_unique<Caza>(player));
	enemigos.push_back(make_unique<TorretaEspacial>(player));
}
void Departure::actualizar(Juego& j) {

	float deltaTime = 0.f;
	if (!pausado) {
		deltaTime = relojDeltaTime.verReinicio();
	}
	else {
		relojDeltaTime.reiniciar();
	}

	if (!pausado) {
		actualizarFondo(deltaTime);

		if (player->estaMuerto()) {
			j.cambiarScena(new FinDelJuego(2,3,4,999));
			return;
		}


		generarItems();

		// hacer que los ítems caigan
		for (auto it = items.begin(); it != items.end(); ) {
			(*it)->actualizar(deltaTime);
			if ((*it)->fueraDePantalla()) {
				it = items.erase(it);
			}
			else {
				++it;
			}
		}

		for (auto it = enemigos.begin(); it != enemigos.end(); ) {
			(*it)->actualizar(deltaTime);
			++it;
		}
		enemyAndShip();

		generarMeteoritos();
		for (auto it = meteoros.begin(); it != meteoros.end(); ) {
			(*it)->actualizar(deltaTime);
			++it;
		}
		meteorAndShip();

		player->recogerItem(items);
		player->actualizar(deltaTime);

		UI.actualizar(player->devolverUltimoItem(), player->verVida(), player->verPuntos(), player->verCanBalas());
	}
	
}
void Departure::dibujar(RenderWindow& window) {
	fondo1.draw(window);
	fondo2.draw(window);

	player->dibujar(window);
	for (auto& enemigo : enemigos) {
		enemigo->dibujar(window);
	}
	for (auto& meteor : meteoros) {
		meteor->dibujar(window);
	}
	for (auto it = items.begin(); it != items.end(); ++it) {
		(*it)->dibujar(window);
	}
	UI.dibujar(window);
	if (pausado) {
		pausa.dibujar(window);
	}
}
void Departure::ProcesoEventos(Juego& j, Event& e) {
	if (pausado) {
		pausa.actualizar(e);
		AccionMenu accion = pausa.verAccion();

		if (accion == AccionMenu::Continuar) {
			pausado = false;
			relojDeltaTime.reanudar();
			relojGeneracion.reanudar();
			relojItem.reanudar();
			player->reanudar();
			pausa.resetearAccion();
		}
		else if (accion == AccionMenu::Reiniciar) {
			delete player;
			Ship* playernew = new ShipN2(200, 30, Vector2f(400, 600), 6.0f);
			j.cambiarScena(new Departure(playernew));
		}
		else if (accion == AccionMenu::SalirDelJuego) {
			j.salir();
		}
		// etc.
	}
	else {
		if (e.type == Event::KeyPressed && e.key.code == Keyboard::Escape) {
			pausado = true;
			relojDeltaTime.pausar();
			relojGeneracion.pausar();
			relojItem.pausar();
			player->pausar();
		}
		player->manejarEventos(e);
	}
}


void Departure::actualizarFondo(float deltaTime) {
	fondo1.move(0, fondoVelocidad * deltaTime);
	fondo2.move(0, fondoVelocidad * deltaTime);

	if (fondo1.getPosition().y >= fondo1.getGlobalBounds().height) {
		fondo1.setPosition(400, fondo2.getPosition().y - fondo1.getGlobalBounds().height);
	}
	if (fondo2.getPosition().y >=  fondo2.getGlobalBounds().height) {
		fondo2.setPosition(400, fondo1.getPosition().y - fondo1.getGlobalBounds().height);
	}
}

void Departure::meteorAndShip() {

	FloatRect boundsJugador = player->getBounds();
	auto& balasJugador = player->obtenerBalas();

	for (auto it = meteoros.begin(); it != meteoros.end();) {

		if (!player->esInvulnerable() && (*it)->colisionaCon(boundsJugador) && !(*it)->estaEnDestruccion()) {
			player->recibirDano((*it)->getDano());
			(*it)->iniciarDestruccion();
			++it;
			continue;
		}

		for (auto itBala = balasJugador.begin(); itBala != balasJugador.end(); ) {
			if ((*itBala)->verBounds().intersects((*it)->getBounds())) {
				(*it)->recibirDano((*itBala)->verDano());
				itBala = balasJugador.erase(itBala);
			}
			else {
				++itBala;
			}
		}

		if ((*it)->estaMuerto() || (*it)->estaFueraDePantalla()) {
			it = meteoros.erase(it);
		}
		else {
			++it;
		}
	}
}
void Departure::enemyAndShip() {

	FloatRect boundsJugador = player->getBounds();
	auto& balasJugador = player->obtenerBalas();

	for (auto it = enemigos.begin(); it != enemigos.end(); ) {

		FloatRect boundsEnemy = (*it)->verBounds();
		auto& balasEnemy = (*it)->obtenerBalas();

		if (!player->esInvulnerable() && (*it)->colisionaCon(boundsJugador) && !(*it)->estaEnDestruccion()) {
			player->recibirDano((*it)->verDanoColision()); 
			(*it)->iniciarDestruccion(); 
		}

		for (auto itBala = balasEnemy.begin(); itBala != balasEnemy.end(); ) {
			if (!player->esInvulnerable() && (*itBala)->verBounds().intersects(boundsJugador) && !(*it)->estaEnDestruccion()) {
				player->recibirDano((*itBala)->verDano());
				itBala = balasEnemy.erase(itBala);
			}
			else {
				++itBala;
			}
		}

		for (auto itBala = balasJugador.begin(); itBala != balasJugador.end(); ) {
			if ((*itBala)->verBounds().intersects(boundsEnemy)) {
				(*it)->recibirDanio((*itBala)->verDano());
				itBala = balasJugador.erase(itBala);
			}
			else {
				++itBala;
			}
		}

		if ((*it)->estaMuerto() || (*it)->estaFueraDePantalla()) {
			it = enemigos.erase(it);
		}
		else {
			++it;
		}
	}
}

void Departure::generarItems() {
	float intervalo = 3.5f;

	if (relojItem.verTiempoTranscurrido() >= intervalo) {
		int random = rand() % 100;

		if (random < 30) {
			// 0–29 → Item_point
			items.push_back(make_unique<ItemPoint>("assets/consumables/items/Item_point.png",
				Vector2f(rand() % 750, -30)));
		}
		else if (random < 50) {
			// 30–49 → Item_rapida
			items.push_back(make_unique<ItemsBullets>("assets/consumables/items/Item_rapida.png",
				Vector2f(rand() % 750, -30), 1, 30));
		}
		else if (random < 65) {
			// 50–64 → Item_doble
			items.push_back(make_unique<ItemsBullets>("assets/consumables/items/Item_doble.png",
				Vector2f(rand() % 750, -30), 5, 20));
		}
		else if (random < 80) {
			// 65–79 → Item_pesada
			items.push_back(make_unique<ItemsBullets>("assets/consumables/items/Item_pesada.png",
				Vector2f(rand() % 750, -30), 3, 20));
		}
		else if (random < 90) {
			// 80–89 → Item_bomba
			items.push_back(make_unique<ItemsBullets>("assets/consumables/items/Item_bomba.png",
				Vector2f(rand() % 750, -30), 4, 10));
		}
		else {
			// 90–99 → Item_life
			items.push_back(make_unique<ItemLife>("assets/consumables/items/Item_life.png",
				Vector2f(rand() % 750, -30)));
		}

		relojItem.reiniciar();
	}
}
void Departure::generarMeteoritos() {
	if (relojGeneracion.verTiempoTranscurrido() >= tiempoMeteoritos) {
		meteoros.push_back(make_unique<Meteor>(80, 30, 5));
		relojGeneracion.reiniciar();
	}
}





