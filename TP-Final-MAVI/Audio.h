#pragma once
#include <SFML/Audio.hpp>
#include <string>

using namespace sf;
using namespace std;

// Clase que encapsula el manejo de sonidos.
// Permite cargar archivos de audio, reproducirlos, detenerlos y configurar.

class Audio {
private:
    SoundBuffer buffer;  
    Sound sound;         

public:
    Audio() {};

    void cargar(const string& rutaArchivo) {
        buffer.loadFromFile(rutaArchivo);
        sound.setBuffer(buffer);
    }

    void play() {
        sound.play();
    }
    void pausa() {
        sound.pause();
    }

    void stop() {
        sound.stop();
    }

    bool estaReproduciendo() const {
        return sound.getStatus() == Sound::Playing;
    }

    void setLoop(bool loop) {
        sound.setLoop(loop);
    };

    void quePitch(float p) {
        sound.setPitch(p);
    }

    void queVolumen(float v) {
        sound.setVolume(v);
    }
};

