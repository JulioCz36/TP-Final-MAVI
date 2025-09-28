#include "PausaMenu.h"

PausaMenu::PausaMenu(RenderWindow& v) : Menu(v) {
    crearBoton("assets/UI/continuar_ui.png", Opciones::Continuar, 12, 13, 3.f, 40 , 129);
    crearBoton("assets/UI/reiniciar_ui.png", Opciones::Reiniciar, 12, 13, 3.f, 90, 129);
    crearBoton("assets/UI/ajustes_ui.png", Opciones::Ajustes, 12, 13, 3.f, 40, 180);
    crearBoton("assets/UI/casa_ui.png", Opciones::VolverAlMenu, 12, 13, 3.f, 90, 180);

	titulo.cargarImagen("assets/UI/titulo_pausa.png");
    titulo.queEscala(3.f ,3.f);
    titulo.quePosition(128 / 2, 60);

    dibujoFondo(false);
    fondoOscuro.setSize(Vector2f(128, 256));
    fondoOscuro.setFillColor(Color(0, 0, 0,150));
}


void PausaMenu::dibujarMenu(RenderTarget& ventana){
    ventana.draw(fondoOscuro);
    Menu::dibujarMenu(ventana);

    titulo.dibujar(ventana);
}
