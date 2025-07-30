#include "MenuPrincipal.h"

MenuPrincipal::MenuPrincipal(RenderWindow& v) : Menu(v,
    {
        Opciones::Comenzar,
        Opciones::ElegirNave,
        Opciones::SalirDelJuego
    },
    {
        "assets/menu/opciones/comenzar_sheet.png",
        "assets/menu/opciones/como_jugar_sheet.png",
        "assets/menu/opciones/salir_del_juego_sheet.png"
    }, 
    { 
        Opciones::SalirDelJuego 
    },
    {
    "assets/menu/carteles/confirmar_salir_del_juego.png", "",""
    },410,60){
    titulo.cargarImagen("assets/menu/titulo_juego.png");
    titulo.quePosition(1280/2,200);
}

void MenuPrincipal::procesoEventos(Juego& j, Event& event) {
    procesoEventosMenu(j, event);
}
void MenuPrincipal::actualizar(Juego& j) { actualizarMenu(); }
void MenuPrincipal::dibujar(RenderWindow& ventana) {
    dibujarMenu(ventana);
    titulo.dibujar(ventana);
    dibujarCartelDeConfrimacion(ventana);
}

void MenuPrincipal::ejecutarAccion(Juego& j, Opciones accion) {
    switch (accion) {
    case Opciones::Comenzar:
        j.cambiarNave();
        break;
    case Opciones::ComoJugar:
        ///j.volverAlMenu();
        break;
    case Opciones::SalirDelJuego:
        j.salir();
        break;
    default:
        break;
    }
}