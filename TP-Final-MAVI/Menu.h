#pragma once
#include <SFML/Graphics.hpp>
#include "Figura.h"
#include "Escenas.h"
#include "Afichmation.h"
#include "Reloj.h"
#include "Audio.h"

using namespace sf;
using namespace std;

class Menu {
private:

    Figura fondo1, fondo2;
    float fondoVelocidad = 50.f;
    Reloj relojDeltaTime;
    bool dibujarFondo = true;

    Audio sonidoDeFondo, sonidoHover;
    int indiceHoverAnterior = -1;

    RenderWindow& ventana;
    vector<shared_ptr<Afichmation>> opciones;
    vector<Opciones> opcionesDisponibles;

    int indiceSeleccionado = 0;

    Opciones accionPendiente = Opciones::Ninguna;

public:
    Menu(RenderWindow& v);

    // === Metodos Principales ===

    void procesoEventosMenu(Juego& j, Event& event);
    virtual void dibujarMenu(RenderTarget& ventana) ;
    void actualizarMenu();

    // === Metodos Para Recortar codigo ===
    void actualizarFondo(float deltaTime);
    void dibujoFondo(bool fondo);
    void actualizarAnimaciones();

    // === LÓGICA DEL MENÚ ===
    int indiceOpcionHover();
    void crearBoton(const string& ruta, Opciones tipo, float anchoFrame, float altoFrame, float escala, float posX, float posY);
    virtual void ejecutarAccion(Juego& j, Opciones accion);

    Opciones verAccion() { return accionPendiente; }
    void resetearAccion() { accionPendiente = Opciones::Ninguna; }
};

