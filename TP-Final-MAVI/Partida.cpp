#include "Partida.h"
#include "DroneDoble.h"

Partida::Partida(RenderWindow& v, Nave* player) :jugador(player), HUD(player->queHabilidad()), pausa(v){

	fondo1.cargarImagen("assets/backgrounds/negro.png");
	fondo2.cargarImagen("assets/backgrounds/negro.png");

	fondo1.quePosition(640, 0);
	fondo2.quePosition(640, fondo1.verPosition().y - fondo1.verGlobalBounds().height);

	relojGeneracion.reiniciar();

	boss = make_unique<Boss>(player,this);

	//enemigos.push_back(make_unique<DroneDoble>(this));
	//enemigos.push_back(make_unique<Caza>(player));
	//enemigos.push_back(make_unique<TorretaEspacial>(player, this));

	for (size_t i = 1; i <= 4; ++i) {
		Texture textura;
		textura.loadFromFile("assets/jugador/lasers/laser0" + to_string(i) + "_impacto.png");
		texturasImpacto.push_back(move(textura));
	}
	
	sonidoImpacto = make_shared<Audio>();
	sonidoItem = make_shared<Audio>();
	sonidoPartNormal = make_shared<Audio>();

	sonidoItem->cargar("assets/sonidos/item_up.wav");
	sonidoItem->queVolumen(50);
	sonidoImpacto->cargar("assets/sonidos/shot_impact.wav");
	sonidoImpacto->queVolumen(55);
	sonidoPartNormal->cargar("assets/sonidos/sonido_batalla_normal.wav");
	sonidoPartNormal->queVolumen(25);

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
			j.finDelJuego(enemigosAbatidos, jugador->verPuntos());
			return;
		}

		generarItems();
		generarAsteroides();

		for (auto& l : lasersJugador) {
			l->actualizar();
		}
		for (auto& l : lasersEnemigos) {
			l->actualizar();
		}
		limpiarBalas();


		if (!bossAparecio && !bossAnimandoEntrada) {
			bossAnimandoEntrada = true;
			bossTimer = 0.f;
		}

		if (bossAnimandoEntrada) {
			bossTimer += deltaTime;

			float startY = -boss->verAltura();
			float endY = 250.f;
			float t = bossTimer / tiempoAnimacionBoss;
			if (t > 1.f) t = 1.f; // por las dudas

			float nuevaY = startY + t * (endY - startY);
			boss->quePositionY(nuevaY);


			// Si terminó la animación:
			if (bossTimer >= tiempoAnimacionBoss) {
				bossAnimandoEntrada = false;
				bossAparecio = true;

				HUD.mostrarVidaBoss(true);            // Ahora mostrar la barra
				HUD.iniciarAnimacionVidaBoss();       // y arrancar la animación de llenado
			}
		}

		for (auto it = impactos.begin(); it != impactos.end(); ) {
			if ((*it)->estaVencido())
				it = impactos.erase(it);
			else
				++it;
		}
		bossYNave(deltaTime);
		enemigoYNave(deltaTime);
		asteroideYNave(deltaTime);
		itemYNave(deltaTime);

		jugador->actualizar(deltaTime);

		HUD.actualizar(ultimo_item, jugador->verVida(), jugador->verPuntos(), jugador->verCanBalas());
		HUD.actualizarAnimacionVidaBoss(deltaTime,  boss->verVidaActual(), boss->verVidaMaxima());

	}else {
		if (sonidoPartNormal->estaReproduciendo()) {
			sonidoPartNormal->pausa();
		}
		relojDeltaTime.reiniciar();
		pausa.actualizarMenu();
	}

}
void Partida::dibujar(RenderWindow& window) {
	fondo1.dibujar(window);
	fondo2.dibujar(window);

	for (auto& l : lasersJugador) {
		l->dibujar(window);
	}
	for (auto& l : lasersEnemigos) {
		l->dibujar(window);
	}

	jugador->dibujar(window);
	for (auto& enemigo : enemigos) {
		enemigo->dibujar(window);
	}
	for (auto& meteor : asteroides) {
		meteor->dibujar(window);
	}
	for (auto it = items.begin(); it != items.end(); ++it) {
		(*it)->dibujar(window);
	}

	boss->dibujar(window);

	for (auto& i : impactos) {
		i->dibujar(window);
	}
	HUD.dibujar(window);
	if (pausado) {
		pausa.dibujarMenu(window);
		pausa.dibujarCartelDeConfrimacion(window);
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

void Partida::agregarLasersJugador(unique_ptr<Bala> laser) {
	lasersJugador.push_back(move(laser));
}
void Partida::agregarLasersEnemigos(unique_ptr<Bala> laser){
	lasersEnemigos.push_back(move(laser));
}
void Partida::limpiarBalas() {
	for (auto it = lasersJugador.begin(); it != lasersJugador.end(); ) {
		if ((*it)->fueraDePantalla()) {
			it = lasersJugador.erase(it);
		}
		else {
			++it;
		}
	}
	for (auto it = lasersEnemigos.begin(); it != lasersEnemigos.end(); ) {
		if ((*it)->fueraDePantalla()) {
			it = lasersEnemigos.erase(it);
		}
		else {
			++it;
		}
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
	fondo1.mover(0, fondoVelocidad * deltaTime);
	fondo2.mover(0, fondoVelocidad * deltaTime);

	if (fondo1.verPosition().y >= fondo1.verGlobalBounds().height) {
		fondo1.quePosition(640, fondo2.verPosition().y - fondo1.verGlobalBounds().height);
	}
	if (fondo2.verPosition().y >= fondo2.verGlobalBounds().height) {
		fondo2.quePosition(640, fondo1.verPosition().y - fondo1.verGlobalBounds().height);
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

		for (auto itBala = lasersJugador.begin(); itBala != lasersJugador.end(); ) {
			if ((*itBala)->verBounds().intersects((*it)->verBounds())) {

				sonidoImpacto->play();

				(*it)->recibirDano((*itBala)->verDano());

				int tipo = (*itBala)->verTipo();
				if (tipo >= 1 && tipo <= 4) {
					impactos.emplace_back(make_unique<ImpactoVisual>(texturasImpacto[tipo - 1], (*itBala)->verSprite().getPosition()));
				}

				itBala = lasersJugador.erase(itBala);
			}
			else {
				++itBala;
			}
		}

		if ((*it)->estaMuerto() || (*it)->estaFueraDePantalla()) {
			it = asteroides.erase(it);
		}
		else {
			++it;
		}
	}
}
void Partida::enemigoYNave(float deltaTime) {

	for (auto it = enemigos.begin(); it != enemigos.end(); ) {
		(*it)->actualizar(deltaTime);
		++it;
	}

	for (auto it = enemigos.begin(); it != enemigos.end(); ) {

		FloatRect boundsEnemy = (*it)->verBounds();

		if (jugador->colisionaCon(boundsEnemy) &&!(*it)->fueDestruido()){
			if(!jugador->esInvulnerable()) {
				jugador->recibirDano((*it)->verDanoColision());
			}
			(*it)->destruir();
		}


		for (auto itBala = lasersEnemigos.begin(); itBala != lasersEnemigos.end(); ) {
			if (jugador->colisionaCon((*itBala)->verBounds())&& !(*it)->fueDestruido()) {

				sonidoImpacto->play();

				if(!jugador->esInvulnerable()){
					jugador->recibirDano((*itBala)->verDano());
				}
				int tipo = (*itBala)->verTipo();
				if (tipo >= 1 && tipo <= 4) {
					impactos.emplace_back(make_unique<ImpactoVisual>(texturasImpacto[tipo - 1], (*itBala)->verSprite().getPosition()));
				}
				
				itBala = lasersEnemigos.erase(itBala);
			}
			else {
				++itBala;
			}
		}

		for (auto itBala = lasersJugador.begin(); itBala != lasersJugador.end(); ) {
			if ((*itBala)->verBounds().intersects(boundsEnemy)) {
				sonidoImpacto->play();

				(*it)->recibirDanio((*itBala)->verDano());

				int tipo = (*itBala)->verTipo(); 
				if (tipo >= 1 && tipo <= 4) {
					impactos.emplace_back(make_unique<ImpactoVisual>(texturasImpacto[tipo - 1], (*itBala)->verSprite().getPosition()));
				}

				itBala = lasersJugador.erase(itBala);
			}
			else {
				++itBala;
			}
		}

		if ((*it)->estaMuerto()) {
			enemigosAbatidos++;
			it = enemigos.erase(it);
		}
		else if ((*it)->estaFueraDePantalla()) {
			it = enemigos.erase(it);
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
void Partida::bossYNave(float deltaTime){

	if (HUD.terminoAnimacionVidaBoss()) {
		boss->actualizar(deltaTime);
	}

	for (auto itBala = lasersJugador.begin(); itBala != lasersJugador.end(); ) {
		if (boss->colisionaCon((*itBala)->verBounds())) {

			if (HUD.terminoAnimacionVidaBoss()) {
				boss->recibirDano((*itBala)->verDano());
			}

			int tipo = (*itBala)->verTipo();
			if (tipo >= 1 && tipo <= 4) {
				impactos.emplace_back(make_unique<ImpactoVisual>(texturasImpacto[tipo - 1], (*itBala)->verSprite().getPosition()));
			}

			itBala = lasersJugador.erase(itBala);
		}
		else {
			++itBala;
		}
	}

	auto & blasters = boss->obtenerHandBlasters();
	for (const auto& laser : blasters) {
		if (jugador->colisionaCon(laser->getGlobalBounds())) {
			if (!jugador->esInvulnerable()) {
				jugador->recibirDano(3);
			}
			jugador->activarInvulnerabilidad(1.0);
		}
	}
}

void Partida::generarItems() {
	float intervalo = 3.5f;

	if (relojItem.verTiempoTranscurrido() >= intervalo) {
		int random = rand() % 100;

		if (random < 30) {
			// 0–29 → Item_puntos
			items.push_back(make_unique<ItemPuntos>());
		}
		else if (random < 50) {
			// 30–49 → Item_rapida
			items.push_back(make_unique<ItemBala>(1));
		}
		else if (random < 65) {
			// 50–64 → Item_doble
			items.push_back(make_unique<ItemBala>(5));
		}
		else if (random < 80) {
			// 65–79 → Item_pesada
			items.push_back(make_unique<ItemBala>(3));
		}
		else if (random < 90) {
			// 80–89 → Item_bomba
			items.push_back(make_unique<ItemBala>(4));
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
