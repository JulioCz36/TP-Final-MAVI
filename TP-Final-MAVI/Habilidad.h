#pragma once
#include <SFML/Graphics.hpp>
#include "Nave.h"
#include "Reloj.h"
class Nave;

using namespace sf;
using namespace std;

class Habilidad{

protected:
    bool activa = false;
    float tiempoRecarga;
    Reloj relojRecarga;

    float duracion;
    Reloj relojDuracion;
    float habilidadProgreso = 1.0f;

public:
    Habilidad(float tiempoRecarga, float duracion);

    bool estaActiva();
    bool estaRecargada();
    float recarga() const;
    void actualizar();

    void pausar();
    void reanudar();

    virtual void aplicarEfecto(Nave& ship) = 0;
    virtual void comportamiento() {};
    virtual string verRutaTextura() = 0;

    virtual void dibujar(RenderWindow& w) {}

};

