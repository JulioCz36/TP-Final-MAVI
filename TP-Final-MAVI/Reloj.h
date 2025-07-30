#pragma once
#include <SFML/System.hpp>
using namespace sf;

class Reloj{
private:
    Clock reloj;
    float tiempoPausado = 0.f;
    bool enPausa = false;
    Time tiempoInicioPausa;

public:
    void pausar() {
        if (!enPausa) {
            enPausa = true;
            tiempoInicioPausa = reloj.getElapsedTime();
        }
    }

    void reanudar() {
        if (enPausa) {
            Time ahora = reloj.getElapsedTime();
            tiempoPausado += (ahora - tiempoInicioPausa).asSeconds();
            enPausa = false;
        }
    }

    float verTiempoTranscurrido() const {
        if (enPausa) {
            return (tiempoInicioPausa.asSeconds() - tiempoPausado);
        }
        else {
            return (reloj.getElapsedTime().asSeconds() - tiempoPausado);
        }
    }

    void reiniciar() {
        reloj.restart();
        tiempoPausado = 0.f;
        enPausa = false;
    }
    float verReinicio() {
        float tiempo = verTiempoTranscurrido();
        reloj.restart();
        return tiempo;
    }
};