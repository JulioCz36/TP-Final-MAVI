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
    //FONDO///
    Figura fondo1, fondo2;
    float fondoVelocidad = 100.f;
    Reloj relojDeltaTime;
    bool dibujarFondo = true;

    RectangleShape fondoOscuro;

    Audio sonidoDeFondo, sonidoHover;
    int indiceHoverAnterior = -1;  
    int indiceConfirmacionAnterior = -1;


    // === Mouse ===
    Figura mouse;
    RenderWindow& ventana;

    // === OPCIONES Y CONFIRMACIONES ===

    vector<shared_ptr<Afichmation>> opcionesConfirmacion;
    bool mostrandoConfirmacion = false;
    int indiceSeleccionado = 0;


    vector<Opciones> accionesQueRequierenConfirmacion; 
    vector<string> rutasCartelesConfirmacion;         

    vector<shared_ptr<Afichmation>> opciones;
    vector<string> rutas_opciones;
    vector<Opciones> opcionesDisponibles;
protected:
    Figura cartelConfirmacion;
    Opciones accionPendiente = Opciones::Ninguna;
    int indiceConfirmacion = 0;

public:
    Menu(RenderWindow& v,vector<Opciones> op, vector<string> rutasOpciones, vector<Opciones> acciones, vector<string> rutas, int posPrincipio, int entreEspacio);

    // === Metodos Principales ===

    void procesoEventosMenu(Juego& j, Event& event);
    virtual void dibujarMenu(RenderWindow& ventana) ;
    void actualizarMenu();

    // === Metodos Para Recortar codigo ===
    void dibujarCartelDeConfrimacion(RenderWindow& ventana);
    void actualizarFondo(float deltaTime);
    void dibujoFondo(bool fondo);
    void actualizarAnimaciones();

    // === LÓGICA DEL MENÚ ===

    bool requiereConfirmacion(Opciones accion);
    Opciones ejecutarOpcion(int i);
    int indiceOpcionHover();
    int indiceConfirmacionHover();
    RenderWindow& verVentana();
    virtual void ejecutarAccion(Juego& j, Opciones accion) {};
    void mostrarConfirmacion(bool mostrar);
    bool mostreConfirmacion();

    Opciones verAccion() { return accionPendiente; }
    void resetearAccion() { accionPendiente = Opciones::Ninguna; }
};

