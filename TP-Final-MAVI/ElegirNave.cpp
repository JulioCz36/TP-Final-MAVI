#include "ElegirNave.h"

ElegirNave::ElegirNave(RenderWindow& v) :
    Menu(v,{Opciones::Jugar,},{"assets/menu/opciones/jugar_sheet.png",},{Opciones::Jugar,},
    {"assets/menu/carteles/confirmar_eligio_nave.png",},640,0), 
    flechaIzquierda("assets/menu/flechas/izquierda_sheet.png",true, 60, 60),
    flechaDerecha("assets/menu/flechas/derecha_sheet.png",true, 60, 60),
    cruzSalida("assets/menu/flechas/salir_sheet.png", true, 60, 60)
{
    flechaIzquierda.Add("off", { 1 }, 1, true);
    flechaIzquierda.Add("on", { 0 }, 1, true);

    flechaDerecha.Add("off", { 0 }, 1, true);
    flechaDerecha.Add("on", { 1 }, 1, true);

    cruzSalida.Add("off", { 0 }, 1, true);
    cruzSalida.Add("on", { 1 }, 1, true);

    opcionesNaves = {
        "assets/menu/carteles/mirage.png",
        "assets/menu/carteles/onyx.png"
    };
    opcionNave.cargarImagen(opcionesNaves[1]);
    opcionNave.quePosition(640, 360);


    cruzSalida.setPosition(40, 40);
    flechaIzquierda.setPosition(280, 720 / 2.f);
    flechaDerecha.setPosition(1000, 720 / 2.f);

}

void ElegirNave::procesoEventos(Juego& j, Event& event) {
    procesoEventosMenu(j, event);
    if (mostreConfirmacion()) return;
    if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {
        Vector2f mousePos = Vector2f(event.mouseButton.x, event.mouseButton.y);

        if (flechaIzquierda.getGlobalBounds().contains(mousePos)) {
            indiceSeleccionado = (indiceSeleccionado - 1 + opcionesNaves.size()) % opcionesNaves.size();
        }
        else if (flechaDerecha.getGlobalBounds().contains(mousePos)) {
            indiceSeleccionado = (indiceSeleccionado + 1) % opcionesNaves.size();
        }
        else if (cruzSalida.getGlobalBounds().contains(mousePos)) {
            cartelConfirmacion.cargarImagen("assets/menu/carteles/confirmar_volver_al_menu.png");
            accionPendiente = Opciones::VolverAlMenu;
            mostrarConfirmacion(true);
            indiceConfirmacion = 0;
        }
    }

}
void ElegirNave::actualizar(Juego& j) {
    actualizarMenu();

    Vector2f mousePos = Vector2f(Mouse::getPosition(verVentana()));

    // Flecha izquierda
    if (flechaIzquierda.getGlobalBounds().contains(mousePos)) {
        flechaIzquierda.Play("on");
    }
    else {
        flechaIzquierda.Play("off");
    }

    // Flecha derecha
    if (flechaDerecha.getGlobalBounds().contains(mousePos)) {
        flechaDerecha.Play("on");
    }
    else {
        flechaDerecha.Play("off");
    }

    // Flecha derecha
    if (cruzSalida.getGlobalBounds().contains(mousePos)) {
        cruzSalida.Play("on");
    }
    else {
        cruzSalida.Play("off");
    }


    flechaIzquierda.Update();
    flechaDerecha.Update();
    cruzSalida.Update();
}
void ElegirNave::dibujar(RenderWindow& ventana){
    dibujarMenu(ventana);

    for (size_t i = 0; i < opcionesNaves.size(); ++i) {
        if (i == indiceSeleccionado) {
            opcionNave.cargarImagen(opcionesNaves[i]);
           
        }
    }
    opcionNave.dibujar(ventana);

    ventana.draw(cruzSalida);
    ventana.draw(flechaIzquierda);
    ventana.draw(flechaDerecha);

    dibujarCartelDeConfrimacion(ventana);
}

void ElegirNave::ejecutarAccion(Juego& j, Opciones accion) {
    switch (accion) {
    case Opciones::Jugar:
        j.queTipoNaveElegido(indiceSeleccionado == 0 ? TipoNave::MIRAGE : TipoNave::ONYX );
        j.iniciarPartida();
        break;
    case Opciones::VolverAlMenu:
        j.volverAlMenu();
        break;
    default:
        break;
    }
}