#pragma once
#include <SFML/Graphics.hpp>
#include "Habilidad.h"
#include "Figura.h"
#include "Afichmation.h"
using namespace sf;
using namespace std;

class HUDPartida{
    Afichmation digito;
    vector<Afichmation> puntos;
    vector<Afichmation>vida;
    vector<Afichmation>cantLasers;

    // === ICONOS ===  
    Figura icon_vida, icon_item;

    //==Vida Boss ==
    Figura vidaBoss, reciVidaBoss;
    float barraVidaBossVisible = 0.f;  // va de 0 a 1
    bool mostrarBarraVidaBoss = false;
    bool animandoVidaBoss = false;

    // === HABILIDAD ===
    Habilidad* habilidad;
    Afichmation iconHabilidad;
public:
    HUDPartida(Habilidad* habi);

    // ===  MÉTODOS PRINCIPALES ===
    void actualizar(const string& itemActivo, int vida_t, int puntos_t, int cantidad);
    void dibujar(RenderWindow& window);

    // === ANIMACIÓN DE HABILIDAD ===
    void habilidadActualizar();
    void actualizarDigitos(vector<Afichmation>& destino, int valor, int posXInicio, int posY, bool izquierdaADerecha);

    // === VIDA BOSS ===
    void iniciarAnimacionVidaBoss();
    void mostrarVidaBoss(bool verVida);
    void actualizarAnimacionVidaBoss(float deltaTime, float vidaActual, float vidaMaxima);
    bool terminoAnimacionVidaBoss();

};

