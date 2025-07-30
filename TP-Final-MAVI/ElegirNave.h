#pragma once
#include <SFML/Graphics.hpp>
#include "Figura.h"
#include "utils.h"
#include "Reloj.h"
#include "Escenas.h"
#include "Menu.h"

using namespace sf;
using namespace std;

class ElegirNave : public Escena, public Menu {

    Afichmation flechaIzquierda, flechaDerecha, cruzSalida;


    vector<string> opcionesNaves;
    Figura opcionNave;
    int indiceSeleccionado = 0;


public:
    ElegirNave(RenderWindow& v);
    void procesoEventos(Juego& j, Event& event) override;
    void actualizar(Juego& j) override;
    void dibujar(RenderWindow& w)override;
    void ejecutarAccion(Juego& j, Opciones accion) override;
};

