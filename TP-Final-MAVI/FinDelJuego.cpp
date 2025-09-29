#include "FinDelJuego.h"

FinDelJuego::FinDelJuego(RenderWindow& v, int _metros) : Menu(v), digito("assets/UI/numeros.png", true, 7, 12), metrosFinales(_metros) {
    crearBoton("assets/UI/reiniciar_ui.png", Opciones::Reiniciar, 12, 13, 2.5f, 28, 180);
    crearBoton("assets/UI/ajustes_ui.png", Opciones::Ajustes, 12, 13, 2.5f, 64, 180);
    crearBoton("assets/UI/casa_ui.png", Opciones::VolverAlMenu, 12, 13, 2.5f, 100, 180);

    for (int i = 0; i < 10; ++i) {
        digito.Add(to_string(i), { i }, 1, true);
    }

    cartel.cargarImagen("assets/UI/cartel_derrota.png");
    cartel.quePosition(1280 / 2.f, 200.5);

    relojConteo.reiniciar();
}

void FinDelJuego::procesoEventos(Juego& j, Event& event){
    procesoEventosMenu(j, event);
}
void FinDelJuego::actualizar(Juego& j){
    actualizarMenu();
    if (contadorActual < metrosFinales && relojConteo.verTiempoTranscurrido() > intervaloConteo) {
        contadorActual += 10; // velocidad de suma
        if (contadorActual > metrosFinales) contadorActual = metrosFinales;
        relojConteo.reiniciar();
    }

    actualizarDigitos(metros, contadorActual, cartel.verPosition().x + 100, cartel.verPosition().y + 88);
}
void FinDelJuego::dibujar(RenderTarget& ventana) {
    dibujarMenu(ventana);

    cartel.dibujar(ventana);
    for (auto& m : metros) {
        ventana.draw(m);
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
