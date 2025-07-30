#include "Boss.h"
#include <iostream>
#include "utils.h"
#include "Partida.h"

Boss::Boss(const Nave* player, Partida* p): partida(p), vidaActual(vidaMaxima) {
	cuerpo.cargarImagen("assets/boss/cuerpo.png");
	cuerpo.quePosition(640, -cuerpo.verGlobalBounds().height);

	// Cargar partes
	partesBoss.emplace_back("manoIzq", "assets/boss/partes/brazo.png");
	partesBoss.back().figura->queEscala(0.6f, 0.58f);
	partesBoss.back().figura->quePosition(cuerpo.verPosition().x - 253, cuerpo.verPosition().y + 66);

	partesBoss.emplace_back("manoDer", "assets/boss/partes/brazo.png");
	partesBoss.back().figura->queEscala(0.6f, 0.58f);
	partesBoss.back().figura->quePosition(cuerpo.verPosition().x + 265, cuerpo.verPosition().y + 66);

	partesBoss.emplace_back("canonIzq", "assets/boss/partes/canon.png");
	partesBoss.back().figura->quePosition(cuerpo.verPosition().x - 134, cuerpo.verPosition().y + 34);

	partesBoss.emplace_back("canonDer", "assets/boss/partes/canon.png");
	partesBoss.back().figura->quePosition(cuerpo.verPosition().x + 156, cuerpo.verPosition().y + 34);


	yendoDerecha = (rand() % 2 == 0);

	//Hibox en personalizada;
	cuerpoHibox = { 120, 290 };
	brazo = { 70, 55 };

	offsetHitboxesBrazo = {
		//derecho
		{110, -27},
		{185, -20},
		{255, -20},
		//izquierdo
		{-100, -25},
		{-175, -20},
		{-245, -15 }
	};

	hitboxCircularBrazoIzq = {Vector2f(-60.f, -97.f), 45.f };
	hitboxCircularBrazoDer = {Vector2f(50.f, -100.f),45.f };

	jugador = const_cast<Nave*>(player);
}

void Boss::recibirDano(float dano){
	vidaActual -= dano;
	if (vidaActual <= 0) {
		vidaActual = 0;
	}
}

void Boss::actualizar(float deltaTime){

	timerGeneral += deltaTime;

	switch (estadoManos) {
	case EstadoAtaqueManos::Esperando:
		if (timerGeneral >= tiempoEspera) {
			cout << "cargando ataque" << endl;
			estadoManos = EstadoAtaqueManos::Preparando;
			timerGeneral = 0.f;
		}
		break;

	case EstadoAtaqueManos::Preparando:
		if (timerGeneral >= tiempoPreparando) {
			cout << "ataco" << endl;
			estadoManos = EstadoAtaqueManos::Disparando;
			crearBlasters();
			activarMovimientoCompleto(true);
			timerGeneral = 0.f;
		}
		break;

	case EstadoAtaqueManos::Disparando:
		actualizarBlasters(deltaTime);

		if (timerGeneral >=  timerAtaque) {
			cout << "esperando" << endl;
			handBlasters.clear();
			estadoManos = EstadoAtaqueManos::Esperando;
			activarMovimientoCompleto(false);
			timerGeneral = 0.f;
		}
		break;
	}

	for (int i = 2; i < partesBoss.size(); i++) {
		int idx = i - 2;

		pivotes[idx] = Vector2f(partesBoss[i].figura->verPosition().x, partesBoss[i].figura->verPosition().y - 60);
		dirs[idx] = jugador->verPos() - pivotes[idx];

		float angulo = atan2(dirs[idx].y, dirs[idx].x) * 180.f / 3.14f;
		partesBoss[i].figura->queRotation(angulo - 90.f);
	}

	if (puedeDisparar()) {
		disparar();
	}
	moverEnX(deltaTime);
}
void Boss::dibujar(RenderWindow& w){
	cuerpo.dibujar(w);

	for (auto& laser : handBlasters) {
		w.draw(*laser);
	}

	for (auto& parte : partesBoss) {
		if (!parte.destruido)
			parte.figura->dibujar(w);
	}
	dibujarHitbox(w);
}

void Boss::quePositionY(float y) {
	float diff = y - cuerpo.verPosition().y;
	cuerpo.mover(0, diff);

	for (auto& parte : partesBoss) {
		if (!parte.destruido)
			parte.figura->mover(0, diff);
	}
}
float Boss::verAltura() {
	return cuerpo.verGlobalBounds().height;
}

void Boss::disparar(){
	if (cadenciaDisparo <= 0.f) return;
	relojDisparo.reiniciar();

	for (int i = 2; i < partesBoss.size(); i++) {

		int idx = i - 2;

		Vector2f dirNormal = normalizar(dirs[idx]);
		cout << "Dir normal Boss[" << idx << "]: " << dirNormal.x << ", " << dirNormal.y << endl;


		float distanciaCabeza = partesBoss[i].figura->verGlobalBounds().height / 2.f;

		Vector2f laserPosition = partesBoss[i].figura->verPosition() + dirNormal * distanciaCabeza;
		partida->agregarLasersEnemigos(make_unique<Bala>(danio, laserPosition, dirNormal, false));


		cout << "Dispara Lasers: " << i - 2 << endl;
	}
}
bool Boss::puedeDisparar() { return relojDisparo.verTiempoTranscurrido() >= cadenciaDisparo; }

void Boss::crearBlasters() {
	handBlasters.clear(); // limpiás por si quedaron del ataque anterior

	auto blasterIzq = make_unique<Afichmation>("assets/boss/ataque_manos/ataque.png",true,44,380);
	blasterIzq->Add("shoot", {0,1,2,3,4,5,0,1,2,3,4,5,},10,true);
	blasterIzq->setColor(Color::Red);
	blasterIzq->setScale(1.f, 0.f);
	blasterIzq->Play("shoot");
	handBlasters.push_back(move(blasterIzq));

	auto blasterDer = make_unique<Afichmation>("assets/boss/ataque_manos/ataque.png", true, 44, 380);
	blasterDer->Add("shoot", { 0,1,2,3,4,5,0,1,2,3,4,5 }, 10, true);
	blasterDer->setColor(Color::Red);
	blasterDer->setScale(1.f, 0.f);
	blasterDer->Play("shoot");
	handBlasters.push_back(move(blasterDer));
}
void Boss::actualizarBlasters(float deltaTime) {
	if (handBlasters.size() < 2) return;

	for (auto& laser : handBlasters) {
		laser->Update();
	}

	float speed = 5.f;

	for (auto& laser : handBlasters) {
		Vector2f escalaActual = laser->getScale();
		if (escalaActual.y < 1.f) {
			escalaActual.y += speed * deltaTime;
			if (escalaActual.y > 1.f) escalaActual.y = 1.f; // Limitar
			laser->setScale(escalaActual.x, escalaActual.y);
		}
	}


	for (int i = 0; i < 2; ++i) {
		Vector2f posMano;
		if (partesBoss[i].nombre == "manoIzq") posMano = partesBoss[i].figura->verPosition();
		else if (partesBoss[i].nombre == "manoDer") posMano = partesBoss[i].figura->verPosition();


		if (yendoDerecha) {
			posMano.x += 5;
		}
		else {
			posMano.x -= 5;
		}

		handBlasters[i]->setPosition(posMano.x, posMano.y + handBlasters[i]->getGlobalBounds().height / 2 + 28);
	}


}
vector<unique_ptr<Afichmation>>& Boss::obtenerHandBlasters(){
	return handBlasters;
}

void Boss::moverEnX(float deltaTime) {
	float desplazamiento = velocidadX * deltaTime;

	if (yendoDerecha)
		cuerpo.mover(desplazamiento,0); 
	else
		cuerpo.mover(-desplazamiento, 0);

	float posX = cuerpo.verPosition().x;

	// Si llegó al límite derecho
	if (posX >= limiteDer) {
		yendoDerecha = false;
	}
	// Si llegó al límite izquierdo
	else if (posX <= limiteIzq) {
		yendoDerecha = true;
	}

	// Actualizá también posiciones de brazos y cañones
	actualizarPartes();
}
void Boss::activarMovimientoCompleto(bool activo) {
	if (activo) {
		limiteIzq = 0.f - cuerpo.verGlobalBounds().width / 2.f + 270;
		limiteDer = 1280.f + cuerpo.verGlobalBounds().width / 2.f - 270;
		velocidadX = 280.f;
	}else {
		limiteIzq = 473.5f;
		limiteDer = 806.5f;
		velocidadX = 200.f;
	}
}
void Boss::actualizarPartes() {
	Vector2f posCuerpo = cuerpo.verPosition();

	float vibracionOffset = 0.f;
	if (estadoManos == EstadoAtaqueManos::Preparando) {
		float frecuenciaVibracion = 20.f;
		float offset = 2.f;
		vibracionOffset = ((static_cast<int>(timerGeneral * frecuenciaVibracion) % 2 == 0) ? -offset : offset);
	}

	for (auto& parte : partesBoss) {
		if (parte.nombre == "manoIzq") {
			parte.figura->quePosition(posCuerpo.x - 253 + vibracionOffset, posCuerpo.y + 66);
		}
		else if (parte.nombre == "manoDer") {
			parte.figura->quePosition(posCuerpo.x + 265 - vibracionOffset, posCuerpo.y + 66);
		}
		else if (parte.nombre == "canonIzq") {
			parte.figura->quePosition(posCuerpo.x - 134, posCuerpo.y + 34);
		}
		else if (parte.nombre == "canonDer") {
			parte.figura->quePosition(posCuerpo.x + 156, posCuerpo.y + 34);
		}
	}
}

bool Boss::colisionaCon(const FloatRect& otro) {
	Vector2f pos = cuerpo.verPosition();

	// Hitbox cuerpo
	FloatRect parteCentral(pos.x - cuerpoHibox.x / 2 + 5, pos.y - cuerpoHibox.y / 2, cuerpoHibox.x, cuerpoHibox.y);

	if (parteCentral.intersects(otro)) return true;

	// Hitboxes brazos
	for (const auto& offset : offsetHitboxesBrazo) {
		FloatRect brazoHitbox(
			pos.x - brazo.x / 2 + offset.x,
			pos.y - brazo.y / 2 + offset.y,
			brazo.x, brazo.y
		);
		if (brazoHitbox.intersects(otro)) return true;
	}

	// Obtener posiciones manos desde partesBoss
	Vector2f posBrazoIzq, posBrazoDer;
	FloatRect manoIzqBounds, manoDerBounds;
	FloatRect canonIzqBounds, canonDerBounds;
	bool manoIzqSet = false, manoDerSet = false, canonIzqSet = false, canonDerSet = false;

	for (const auto& parte : partesBoss) {
		if (parte.nombre == "manoIzq") {
			posBrazoIzq = parte.figura->verPosition() + hitboxCircularBrazoIzq.offset;
			manoIzqBounds = parte.figura->verGlobalBounds();
			manoIzqSet = true;
		}
		else if (parte.nombre == "manoDer") {
			posBrazoDer = parte.figura->verPosition() + hitboxCircularBrazoDer.offset;
			manoDerBounds = parte.figura->verGlobalBounds();
			manoDerSet = true;
		}
		else if (parte.nombre == "canonIzq") {
			canonIzqBounds = parte.figura->verGlobalBounds();
			canonIzqSet = true;
		}
		else if (parte.nombre == "canonDer") {
			canonDerBounds = parte.figura->verGlobalBounds();
			canonDerSet = true;
		}
	}

	if (manoIzqSet && rectIntersectsCircle(otro, posBrazoIzq, hitboxCircularBrazoIzq.radio)) return true;
	if (manoDerSet && rectIntersectsCircle(otro, posBrazoDer, hitboxCircularBrazoDer.radio)) return true;

	if (manoIzqSet && manoIzqBounds.intersects(otro)) return true;
	if (manoDerSet && manoDerBounds.intersects(otro)) return true;

	if (canonIzqSet && canonIzqBounds.intersects(otro)) return true;
	if (canonDerSet && canonDerBounds.intersects(otro)) return true;

	return false;
}
bool Boss::rectIntersectsCircle(const FloatRect& rect, const Vector2f& circleCenter, float circleRadius) {
	float nearestX = std::max(rect.left, std::min(circleCenter.x, rect.left + rect.width));
	float nearestY = std::max(rect.top, std::min(circleCenter.y, rect.top + rect.height));
	float deltaX = circleCenter.x - nearestX;
	float deltaY = circleCenter.y - nearestY;
	return (deltaX * deltaX + deltaY * deltaY) < (circleRadius * circleRadius);
}

void Boss::dibujarHitbox(RenderWindow& w) {
	Vector2f pos = cuerpo.verPosition();

	auto crearHitbox = [&](const FloatRect& rect, Color color) {
		RectangleShape box(Vector2f(rect.width, rect.height));
		box.setPosition(rect.left, rect.top);
		box.setFillColor(Color::Transparent);
		box.setOutlineColor(color);
		box.setOutlineThickness(1.f);
		w.draw(box);
	};
	auto crearHitboxCirculo = [&](const Vector2f& centro, float radio, Color color) {
		CircleShape circulo(radio);
		circulo.setOrigin(radio, radio);
		circulo.setPosition(centro);
		circulo.setFillColor(Color::Transparent);
		circulo.setOutlineColor(color);
		circulo.setOutlineThickness(1.f);
		w.draw(circulo);
		};


	FloatRect parteCentral(pos.x - cuerpoHibox.x / 2 + 5, pos.y - cuerpoHibox.y / 2, cuerpoHibox.x, cuerpoHibox.y);
	crearHitbox(parteCentral, Color::Red);

	// Dibujo hitboxes brazo con loop y distintos colores si querés
	std::vector<Color> colores = { Color::Blue, Color::Green, Color::Yellow };
	for (size_t i = 0; i < offsetHitboxesBrazo.size(); ++i) {
		const auto& offset = offsetHitboxesBrazo[i];
		FloatRect brazoHitbox(
			pos.x - brazo.x / 2 + offset.x,
			pos.y - brazo.y / 2 + offset.y,
			brazo.x, brazo.y
		);
		crearHitbox(brazoHitbox, colores[i % colores.size()]);
	}


	// Obtener posiciones de las manos desde partesBoss
	Vector2f posBrazoIzq, posBrazoDer;
	bool manoIzqSet = false, manoDerSet = false;

	for (const auto& parte : partesBoss) {
		if (parte.nombre == "manoIzq") {
			posBrazoIzq = parte.figura->verPosition();
			manoIzqSet = true;
		}
		else if (parte.nombre == "manoDer") {
			posBrazoDer = parte.figura->verPosition();
			manoDerSet = true;
		}
	}

	if (manoIzqSet) {
		crearHitboxCirculo(posBrazoIzq + hitboxCircularBrazoIzq.offset, hitboxCircularBrazoIzq.radio, Color::Blue);
	}
	if (manoDerSet) {
		crearHitboxCirculo(posBrazoDer + hitboxCircularBrazoDer.offset, hitboxCircularBrazoDer.radio, Color::Green);
	}
}
