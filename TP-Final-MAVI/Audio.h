#pragma once
#include <SFML/Audio.hpp>
#include <string>

using namespace sf;
using namespace std;

// Clase que encapsula el manejo de sonidos.
// Permite cargar archivos de audio, reproducirlos, detenerlos y configurar.

class Audio {
private:
    SoundBuffer buffer;  // almacena los datos del archivo de sonido.
    Sound sound;         // se encarga de reproducir el sonido.

public:
    Audio() {};
    // Carga un archivo de sonido desde la ruta indicada.
    void cargar(const string& rutaArchivo) {
        buffer.loadFromFile(rutaArchivo);
        sound.setBuffer(buffer);
    }

    // Reproduce el sonido cargado desde el inicio.
    void play() {
        sound.play();
    }
    void pausa() {
        sound.pause();
    }

    // Detiene la reproducción del sonido actual.
    void stop() {
        sound.stop();
    }

    // Verifica si el sonido se está reproduciendo actualmente.
    bool estaReproduciendo() const {
        return sound.getStatus() == Sound::Playing;
    }

    // Establece si el sonido debe repetirse automáticamente una vez que finalice.
    void setLoop(bool loop) {
        sound.setLoop(loop);
    };

    // Cambia el pitch (tono) del sonido.
    void quePitch(float p) {
        sound.setPitch(p);
    }

    // Establece el volumen del sonido.
    void queVolumen(float v) {
        sound.setVolume(v);
    }
};

