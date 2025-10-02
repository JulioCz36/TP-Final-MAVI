#include "MenuPrincipal.h"

MenuPrincipal::MenuPrincipal(RenderWindow& v) : Menu(v){
    crearBoton("assets/UI/play_ui.png", Opciones::Comenzar, 29, 14, 3.f, 128 / 2, 130);
    crearBoton("assets/UI/ayuda_ui.png", Opciones::ComoJugar, 12, 13, 3.f, 23, 180);
    crearBoton("assets/UI/ajustes_ui.png", Opciones::Ajustes, 12, 13, 3.f, 64, 180);
    crearBoton("assets/UI/salir_ui.png", Opciones::SalirDelJuego, 12, 13, 3.f, 105, 180);

	titulo.cargarImagen("assets/UI/titulo.png");
	titulo.queEscala(2.5, 2.5);
	titulo.quePosition(128/2, 60);
}

void MenuPrincipal::procesoEventos(Juego& j, Event& event) {
    procesoEventosMenu(j, event);
}
void MenuPrincipal::actualizar(Juego& j) { actualizarMenu(); }
void MenuPrincipal::dibujar(RenderTarget& ventana) {
    dibujarMenu(ventana);
    titulo.dibujar(ventana);
}
