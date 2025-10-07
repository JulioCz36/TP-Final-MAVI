#include "FinDelJuego.h"

FinDelJuego::FinDelJuego(RenderWindow& v, int _metros) : Menu(v), digito("assets/UI/numeros.png", true, 7, 12), metrosFinales(_metros) {
    crearBoton("assets/UI/reiniciar_ui.png", Opciones::Reiniciar, 12, 13, 3.f, 23, 180);
    crearBoton("assets/UI/ajustes_ui.png", Opciones::Ajustes, 12, 13, 3.f, 64, 180);
    crearBoton("assets/UI/casa_ui.png", Opciones::VolverAlMenu, 12, 13, 3.f, 105, 180);

    victoria = metrosFinales >= 5000.f; 

    for (int i = 0; i < 10; ++i) {
        digito.Add(to_string(i), { i }, 1, true);
    }

    if (victoria) {
        titulo.cargarImagen("assets/UI/titulo_victoria.png");
        cartel.cargarImagen("assets/UI/cartel_victoria.png");
    }
    else {
        titulo.cargarImagen("assets/UI/titulo_derrota.png");
        cartel.cargarImagen("assets/UI/cartel_derrota.png");
    }

	titulo.queEscala(2.f, 2.f);
    titulo.quePosition(128 / 2.f, 60);
    cartel.quePosition(128 / 2.f, 120);

    relojConteo.reiniciar();
}

void FinDelJuego::procesoEventos(Juego& j, Event& event){
    procesoEventosMenu(j, event);
}
void FinDelJuego::actualizar(Juego& j){
    actualizarMenu();

    if (!victoria) {
        if (contadorActual < metrosFinales && relojConteo.verTiempoTranscurrido() > intervaloConteo) {
            contadorActual += 10; // velocidad de suma
            if (contadorActual > metrosFinales) contadorActual = metrosFinales;
            relojConteo.reiniciar();
        }

        actualizarDigitos(metros, contadorActual, cartel.verPosition().x + 4, cartel.verPosition().y + 13);
    }
}
void FinDelJuego::dibujar(RenderTarget& ventana) {
    dibujarMenu(ventana);

    cartel.dibujar(ventana);
    titulo.dibujar(ventana);
    if (!victoria) {
        for (auto& m : metros) {
            ventana.draw(m);
        }
    }
}

void FinDelJuego::actualizarDigitos(vector<Afichmation>& destino, int valor, int posXInicio, int posY) {
    destino.clear();
    string str = to_string(valor);

    float espaciado = 8.f * digito.getScale().x;

    for (size_t i = 0; i < str.size(); ++i) {
        string nombre(1, str[i]);
        Afichmation nuevoDigito = digito;
        nuevoDigito.Play(nombre);

        float posX = posXInicio + i * espaciado;
        nuevoDigito.setPosition(posX, posY);
        nuevoDigito.Update();
        destino.push_back(nuevoDigito);
    }
}
