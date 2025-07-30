#include "Bala.h"
#include "utils.h"

Bala::Bala(int tipo, Vector2f position, Vector2f dir, bool color) : direccion(normalizar(dir)), tipo(tipo) {
    switch (tipo) {
    case 1:
        if (color) {
            bala.cargarImagen("assets/jugador/lasers/laser01.png");
        }else {
            bala.cargarImagen("assets/enemigos/lasers/laser01.png");
        }
        velocidad = 8.0f;
        dano = 3.0f;
        break;
    case 2:
        if (color) {
            bala.cargarImagen("assets/jugador/lasers/laser02.png");
        }
        else {
            bala.cargarImagen("assets/enemigos/lasers/laser02.png");
        }
        velocidad = 5.0f;
        dano = 5.0f;
        break;
    case 3:
        if (color) {
            bala.cargarImagen("assets/jugador/lasers/laser03.png");
        }
        else {
            bala.cargarImagen("assets/enemigos/lasers/laser03.png");
        }
        velocidad = 3.0f;
        dano = 8.0f;
        break;
    case 4:
        if (color) {
            bala.cargarImagen("assets/jugador/lasers/laser04.png");
        }
        else {
            bala.cargarImagen("assets/enemigos/lasers/laser04.png");
        }
        velocidad = 2.5f;
        dano = 10.0f;
        break;
    }


    bala.quePosition(position.x, position.y);
    float angulo = atan2(direccion.y, direccion.x) * 180 / 3.14159f;
    bala.queRotation(angulo + 90);
}

void Bala::actualizar() {bala.mover(direccion.x * velocidad, direccion.y * velocidad);}

void Bala::dibujar(RenderWindow& window) {bala.dibujar(window);}

Sprite& Bala::verSprite() {return bala.verSprite();}

bool Bala::fueraDePantalla() {return bala.verPosition().y < - bala.verGlobalBounds().height;}

FloatRect Bala::verBounds()  {return bala.verSprite().getGlobalBounds();}

float Bala::verDano(){return dano;}
int Bala::verTipo() { return Bala::tipo; }
