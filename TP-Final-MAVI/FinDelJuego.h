#pragma once
#include <SFML/Graphics.hpp>
#include "Figura.h"
#include "Escenas.h"
#include "Menu.h"

using namespace sf;
using namespace std;


class FinDelJuego : public Escena, public Menu {
	Afichmation digito;
	vector<Afichmation> enemigo;
	vector<Afichmation>punto;
	vector<Afichmation>puntosFinales;

    Figura cartel;

	int contadorActual = 2;
	int puntosFinalesObjetivo = 0;
	Reloj relojConteo;
	float intervaloConteo = 0.05f;


public:
	FinDelJuego(RenderWindow& v,int enemigos,int puntos);
	void procesoEventos(Juego& j, Event& event) override;
	void actualizar(Juego& j) override;
	void dibujar(RenderWindow& w)override;

    void ejecutarAccion(Juego& j, Opciones accion) override;
	void actualizarDigitos(vector<Afichmation>& destino, int valor, int posXFin, int posY);
};

