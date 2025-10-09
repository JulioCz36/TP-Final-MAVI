#include "Asteroide.h"

Asteroide::Asteroide(const string& texture, float speedMeteor, Vector2f dir, Vector2f pos) :
	destruccion("assets/meteoritos/meteorito_destruido.png", true, 8, 8), velocidad(speedMeteor), direccion(normalizar(dir)) {

	asteroide.cargarImagen(texture);
	asteroide.quePosition(pos.x, pos.y);
	
	destruccion.setScale(2, 2);
	destruccion.Add("destruccion", { 0,1,2,3 }, 8, false);
}

void Asteroide::dibujar(RenderTarget& w) {
	if (enDestruccion) {
		w.draw(destruccion);
	}
	else {
		asteroide.dibujar(w);
	}
}
void Asteroide::actualizar(float deltaTime, float posY) {

	if (enDestruccion) {
		destruccion.Update();
		return;
	}

	asteroide.mover(direccion.x * velocidad * deltaTime, 0.f);

	if (asteroide.verPosition().x <= -15.f) {
		direccion.x = 1.f; 
	}
	else if (asteroide.verPosition().x + asteroide.verGlobalBounds().width >= 155.f) {
		direccion.x = -1.f; 
	}
	
	float limiteY = posY + 500.f;
	if (asteroide.verPosition().y > limiteY) {
		fueraDePantalla = true;
	}
}

void Asteroide::recibirDano(float danoRecibido) {
	vida -= danoRecibido;
	if (vida <= 0) {
		vida = 0;
		iniciarDestruccion();
	}
}
float Asteroide::verDano() const {return dano;}

void Asteroide::iniciarDestruccion() {
	if (!enDestruccion) {
		enDestruccion = true;
		destruccion.setPosition(asteroide.verPosition());
		destruccion.Play("destruccion");
	}
}
bool Asteroide::estaEnDestruccion() const {return enDestruccion;}
bool Asteroide::estaMuerto() {return destruccion.IsFinished("destruccion");}

bool  Asteroide::estaFueraDePantalla() {return fueraDePantalla;}
FloatRect Asteroide::verBounds() {return asteroide.verGlobalBounds();}

Vector2f Asteroide::verPos() {
	return asteroide.verPosition();
};