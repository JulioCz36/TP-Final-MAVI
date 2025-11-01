#pragma once
#include <SFML/Audio.hpp>
using namespace sf;
using namespace std;


class AudioManager{
    static bool sonidoActivado;

public:
    static void setSonidoActivado(bool estado) { sonidoActivado = estado; }

    static bool getSonidoActivado() { return sonidoActivado; }

    static void reproducirSonido(Sound& sonido) {
        if (sonidoActivado)
            sonido.play();
    }

};

