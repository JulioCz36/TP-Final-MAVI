#include "FinDelJuego.h"

FinDelJuego::FinDelJuego(RenderWindow& v, int enemigos, int puntos) : Menu(v,
    {
        Opciones::Reiniciar,
        Opciones::VolverAlMenu,
        Opciones::SalirDelJuego
    },
    {
        "assets/menu/opciones/reiniciar_sheet.png",
        "assets/menu/opciones/volver_al_menu_sheet.png",
        "assets/menu/opciones/salir_del_juego_sheet.png"
    },
    {
        Opciones::Reiniciar,
        Opciones::VolverAlMenu,
        Opciones::SalirDelJuego
    },
    {
    "assets/menu/carteles/confirmar_reiniciar.png",
    "assets/menu/carteles/confirmar_volver_al_menu.png",
    "assets/menu/carteles/confirmar_salir_del_juego.png"
    }
    , 425.0, 50), digito("assets/hud/numeros_sheet.png", true, 19, 19) {

    for (int i = 0; i < 11; ++i) {
        digito.Add(to_string(i), { i }, 1, true);
    }
    digito.setScale(1.5,1.5);

    cartel.cargarImagen("assets/menu/carteles/fin_del_juego_loser.png");
    cartel.quePosition(1280 / 2.f, 200.5);

    actualizarDigitos(enemigo, enemigos, cartel.verPosition().x - 40, cartel.verPosition().y + 18);
    actualizarDigitos(punto, puntos, cartel.verPosition().x + 210, cartel.verPosition().y + 18);
    puntosFinalesObjetivo = (enemigos * 100) + (puntos * 2);
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
void FinDelJuego::dibujar(RenderWindow& ventana) {
    dibujarMenu(ventana);

    cartel.dibujar(ventana);
    for (auto& e : enemigo) {
        ventana.draw(e);
    }
    for (auto& p : punto) {
        ventana.draw(p);
    }
    for (auto& ps : puntosFinales) {
        ventana.draw(ps);
    }


    dibujarCartelDeConfrimacion(ventana);
}
void FinDelJuego::ejecutarAccion(Juego& j, Opciones accion) {
    switch (accion) {
    case Opciones::Reiniciar:
        j.reiniciar(); 
        break;
    case Opciones::VolverAlMenu:
        j.volverAlMenu();
        break;
    case Opciones::SalirDelJuego:
        j.salir();  
        break;
    default:
        break;
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
