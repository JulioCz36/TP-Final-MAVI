#include "Asteroide.h"

Asteroide::Asteroide(const string& texture, float speedMeteor) : 
	destruccion("assets/meteoritos/meteorito_destruido.png", true, 8, 8), velocidad(speedMeteor){

	destruccion.Add("destruccion", { 0,1,2,3 }, 8, false);
}

void Asteroide::dibujar(RenderTarget& window) {window.draw(asteroide);}
void Asteroide::actualizar(float deltaTime) {
	asteroide.Update();
	if (!enDestruccion) {
		asteroide.Play("idle");
		asteroide.move(0, velocidad * deltaTime);
		if (asteroide.getGlobalBounds().top > 720) {
			fueraDePantalla = true;
		}
	}
}

void Asteroide::recibirDano(float danoRecibido) {
	vida -= danoRecibido;
	if (vida <= 0) {
		iniciarDestruccion();
	}
}
float Asteroide::verDano() const {return dano;}

void Asteroide::iniciarDestruccion() {
	if (!enDestruccion) {
		enDestruccion = true;
		asteroide.Play("destroyed");
		vida = 0;
	}
}
bool Asteroide::estaEnDestruccion() const {return enDestruccion;}

bool Asteroide::estaMuerto() {return asteroide.IsFinished("destroyed");}
bool  Asteroide::estaFueraDePantalla() {return fueraDePantalla;}
FloatRect Asteroide::verBounds() {return asteroide.getGlobalBounds();}
