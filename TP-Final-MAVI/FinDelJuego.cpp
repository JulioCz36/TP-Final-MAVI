#include "FinDelJuego.h"

FinDelJuego::FinDelJuego(RenderWindow& v, int kilometros) : Menu(v), digito("assets/hud/numeros_sheet.png", true, 19, 19) {

    for (int i = 0; i < 11; ++i) {
        digito.Add(to_string(i), { i }, 1, true);
    }
    digito.setScale(1.5,1.5);

    cartel.cargarImagen("assets/menu/carteles/fin_del_juego_loser.png");
    cartel.quePosition(1280 / 2.f, 200.5);

    actualizarDigitos(punto, kilometros, cartel.verPosition().x + 210, cartel.verPosition().y + 18);
    contadorActual = 0;
    relojConteo.reiniciar();
}

void FinDelJuego::procesoEventos(Juego& j, Event& event){
    procesoEventosMenu(j, event);
}
void FinDelJuego::actualizar(Juego& j){
    actualizarMenu();
    if (contadorActual < puntosFinalesObjetivo && relojConteo.verTiempoTranscurrido()> intervaloConteo) {
        contadorActual += 10; // velocidad de suma
        if (contadorActual > puntosFinalesObjetivo)
            contadorActual = puntosFinalesObjetivo;

        actualizarDigitos(puntosFinales, contadorActual, cartel.verPosition().x + 100, cartel.verPosition().y + 88);
        relojConteo.reiniciar();
    }
}
void FinDelJuego::dibujar(RenderTarget& ventana) {
    dibujarMenu(ventana);

    cartel.dibujar(ventana);
    for (auto& p : punto) {
        ventana.draw(p);
    }
}

void FinDelJuego::actualizarDigitos(vector<Afichmation>& destino, int valor, int posXInicio, int posY) {
    destino.clear();
    string str = to_string(valor);

    float escala = digito.getScale().x; 
    float anchoDigito = 19.f * escala;

    for (size_t i = 0; i < str.size(); ++i) {
        string nombre(1, str[i]);
        Afichmation nuevoDigito = digito;
        nuevoDigito.Play(nombre);

        float posX = posXInicio + i * anchoDigito;
        nuevoDigito.setPosition(posX, posY);
        nuevoDigito.Update();
        destino.push_back(nuevoDigito);
    }
}
