#pragma once
#include <SFML/Graphics.hpp>
#include "Afichmation.h"
#include "Reloj.h"
#include "Bala.h"
#include "Audio.h"

using namespace sf;
using namespace std;

class Partida;


class Enemigo{

    // === VIDA Y DAÑO ===
    int vida;
    bool destruido = false;

    float velocidad;
    float danoColision = 5;

protected:

    Partida* partida = nullptr;

    Afichmation enemigo;

    Audio sonidoDisparo;

    // === DISPARO ===
    float cadenciaDisparo;
    Reloj relojDisparo;

    int danio;


public:
    Enemigo(Partida* p, const string& texture, int frameWidth, int frameHeight, initializer_list<int>idle, initializer_list<int>shot, initializer_list<int>destroyed, float vel, int hp, float cadencia, int queBala);
    Enemigo(const string& texture, int frameWidth, int frameHeight,initializer_list<int> idle, initializer_list<int> shot, initializer_list<int> destroyed,float vel, int hp, float cadencia, int queBala);

    // ===  MÉTODOS PRINCIPALES ===

    void actualizar(float deltaTime);
    void dibujar(RenderWindow& window);
    virtual void comportamiento(float deltaTime) = 0;

    // === ANIMACIÓN ===
    void actualizarAnimacion();

    // === COLISIÓN Y VIDA ===
    bool colisionaCon(const FloatRect& objeto);
    void recibirDanio(int dmg);
    bool estaMuerto() ;
    bool fueDestruido() const;
    void destruir();


    // === DISPARO ===
    virtual void disparar();
    bool puedeDisparar();

    // === POSICIÓN Y BOUNDS ===
    FloatRect verBounds();
    Vector2f verPosition();
    void quePosition(Vector2f pos);
    void queAngle(float angulo);
    void mover(Vector2f movimiento);
    bool estaFueraDePantalla();

    // === UTILIDADES ===
    float verDanoColision();
    virtual Vector2f verDireccionDisparo() const;
    float verVelocidad() { return velocidad; };
    void queDanoColision(float dano) { danoColision = dano; };
};

