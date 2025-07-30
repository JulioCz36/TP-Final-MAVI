#include "Asteroide.h"

Asteroide::Asteroide(const string& texture, int anchura, int altura,float speedMeteor, float vidaMeteor, float danoMeteor) :
	asteroide(texture,true, anchura, altura),velocidad(speedMeteor), vida(vidaMeteor), vidaMaxima(vidaMeteor), dano(danoMeteor) {
	asteroide.Add("idle", { 0 }, 30, true);
	asteroide.Add("destroyed", { 1 }, 30, false);
	asteroide.setPosition(rand() % (1280 - anchura), -altura / 2.f);
}

void Asteroide::dibujar(RenderWindow& window) {window.draw(asteroide);}
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

bool Asteroide::colisionaCon(const FloatRect& objeto) {return asteroide.getGlobalBounds().intersects(objeto);}
bool Asteroide::estaMuerto() {return vida <= 0 && asteroide.IsFinished("destroyed");}
bool  Asteroide::estaFueraDePantalla() {return fueraDePantalla;}
FloatRect Asteroide::verBounds() {return asteroide.getGlobalBounds();}
