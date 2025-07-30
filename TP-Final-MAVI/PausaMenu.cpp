#include "PausaMenu.h"

PausaMenu::PausaMenu(RenderWindow& v) : Menu(v,
    {
        Opciones::Continuar,
        Opciones::Reiniciar,
        Opciones::ElegirNave,
        Opciones::VolverAlMenu,
        Opciones::SalirDelJuego
    },
    {
        "assets/menu/opciones/continuar_sheet.png",
        "assets/menu/opciones/reiniciar_sheet.png",
        "assets/menu/opciones/cambiar_nave_sheet.png",
        "assets/menu/opciones/volver_al_menu_sheet.png",
        "assets/menu/opciones/salir_del_juego_sheet.png"
    },
    {
        Opciones::Reiniciar,
        Opciones::ElegirNave,
        Opciones::VolverAlMenu,
        Opciones::SalirDelJuego
    }, 
    {
        "assets/menu/carteles/confirmar_reiniciar.png",
        "assets/menu/carteles/confirmar_cambiar_nave.png",
        "assets/menu/carteles/confirmar_volver_al_menu.png",
        "assets/menu/carteles/confirmar_salir_del_juego.png"
    }, 130,60) {
    dibujoFondo(false);
    fondoOscuro.setSize(Vector2f(1280, 720));
    fondoOscuro.setFillColor(Color(0, 0, 0,150));
}

void PausaMenu::ejecutarAccion(Juego& j, Opciones accion) {
    switch (accion) {
    case Opciones::Continuar:
        j.reanudar();
        break;
    case Opciones::Reiniciar:
        j.marcarParaReiniciar();
        j.reanudar();
        break;
    case Opciones::ElegirNave:
        j.cambiarNave();
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

void PausaMenu::dibujarMenu(RenderWindow& ventana){
    ventana.draw(fondoOscuro);
    Menu::dibujarMenu(ventana);
}
