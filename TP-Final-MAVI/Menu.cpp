#include "Menu.h"
Menu::Menu(RenderWindow& v, vector<Opciones> op, vector<string> rutasOpciones, vector<Opciones> acciones, vector<string> rutas, int posPrincipio, int entreEspacio) :
    ventana(v), opcionesDisponibles(op), rutas_opciones(rutasOpciones), accionesQueRequierenConfirmacion(acciones), rutasCartelesConfirmacion(rutas) {
    fondo1.cargarImagen("assets/backgrounds/violeta.png");
    fondo2.cargarImagen("assets/backgrounds/violeta.png");

    fondo1.quePosition(640, 0);
    fondo2.quePosition(640, fondo1.verPosition().y - fondo1.verGlobalBounds().height);

    fondoOscuro.setSize(Vector2f(1280, 720));
    fondoOscuro.setFillColor(Color(0, 0, 0));

    mouse.cargarImagen("assets/hud/cursor.png"); 
    ventana.setMouseCursorVisible(false);

    for (size_t i = 0; i < rutas_opciones.size(); ++i) {
        auto opcion = make_shared<Afichmation>(rutas_opciones[i], true,300, 80);
        opcion->Add("off", { 0 }, 1, true);
        opcion->Add("on", { 1 }, 1, true);

        float y = posPrincipio + i * (60 + entreEspacio);
        opcion->setPosition(1280 / 2.f, y);


        opciones.push_back(opcion);
    }

    cartelConfirmacion.quePosition(640, 360);

    vector<string> rutasConfirmacion = {
        "assets/menu/opciones/si_sheet.png",
        "assets/menu/opciones/no_sheet.png"
    };
    for (size_t i = 0; i < rutasConfirmacion.size(); ++i) {
        auto opcion = make_shared<Afichmation>(rutasConfirmacion[i], true,50, 50);
        opcion->Add("off", { 0 }, 1, true);
        opcion->Add("on", { 1 }, 1, true);

        opcion->setPosition((cartelConfirmacion.verPosition().x - 80) + (i * 150), cartelConfirmacion.verPosition().y + 90);
        opcionesConfirmacion.push_back(opcion);
    }

    sonidoDeFondo.cargar("assets/sonidos/sonido_menu.wav");
    sonidoDeFondo.queVolumen(25);
    sonidoHover.cargar("assets/sonidos/hover.wav");
    sonidoHover.queVolumen(20);

};

void Menu::procesoEventosMenu(Juego& j, Event& event) {
    if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {
        if (mostrandoConfirmacion) {
            if (opcionesConfirmacion[indiceConfirmacion]->getGlobalBounds().contains(mouse.verPosition())) {
                if (indiceConfirmacion == 0)
                    ejecutarAccion(j, accionPendiente);

                mostrandoConfirmacion = false;
                accionPendiente = Opciones::Ninguna;
            }
            return;
        }

        int hover = indiceOpcionHover();
        if (hover != -1) {
            accionPendiente = ejecutarOpcion(hover);
            if (requiereConfirmacion(accionPendiente)) {
                mostrandoConfirmacion = true;
                indiceConfirmacion = 0;
                auto it = std::find(accionesQueRequierenConfirmacion.begin(), accionesQueRequierenConfirmacion.end(), accionPendiente);
                if (it != accionesQueRequierenConfirmacion.end()) {
                    size_t index = distance(accionesQueRequierenConfirmacion.begin(), it);
                    if (index < rutasCartelesConfirmacion.size()) {
                        cartelConfirmacion.cargarImagen(rutasCartelesConfirmacion[index]);
                    }
                }
            }
            else {
                ejecutarAccion(j, accionPendiente);
                accionPendiente = Opciones::Ninguna;
            }
        }
    }
}
void Menu::dibujarMenu(RenderWindow& ventana) {
    if (dibujarFondo) {
        fondo1.dibujar(ventana);
        fondo2.dibujar(ventana);
    }
    for (size_t i = 0; i < opciones.size(); ++i) {
        ventana.draw(*opciones[i]);
    }
};
void Menu::actualizarMenu() {

    if (!sonidoDeFondo.estaReproduciendo()) {
        sonidoDeFondo.play();
    }

    float deltaTime = relojDeltaTime.verReinicio();
    Vector2i posicionMouse = Mouse::getPosition(ventana);
    mouse.quePosition(static_cast<float>(posicionMouse.x), static_cast<float>(posicionMouse.y));

    actualizarFondo(deltaTime);
    actualizarAnimaciones();
}

void Menu::dibujarCartelDeConfrimacion(RenderWindow& ventana) {
    if (mostrandoConfirmacion) {
        ventana.draw(fondoOscuro);
        cartelConfirmacion.dibujar(ventana);
        for (int i = 0; i < 2; ++i) {
            ventana.draw(*opcionesConfirmacion[i]);
        }
    }
    mouse.dibujar(ventana);
};
void Menu::actualizarFondo(float deltaTime) {
    fondo1.mover(0, fondoVelocidad * deltaTime);
    fondo2.mover(0, fondoVelocidad * deltaTime);

    if (fondo1.verPosition().y >= fondo1.verGlobalBounds().height) {
        fondo1.quePosition(640, fondo2.verPosition().y - fondo1.verGlobalBounds().height);
    }
    if (fondo2.verPosition().y >= fondo2.verGlobalBounds().height) {
        fondo2.quePosition(640, fondo1.verPosition().y - fondo1.verGlobalBounds().height);
    }
}
void Menu::dibujoFondo(bool fondo){
    dibujarFondo = fondo;
}
void Menu::actualizarAnimaciones() {

    if (mostrandoConfirmacion) {
        int hoverConfirmacion = indiceConfirmacionHover();
        for (int i = 0; i < 2; ++i) {
            opcionesConfirmacion[i]->Update();

            if (i == hoverConfirmacion) {
                if (i != indiceConfirmacionAnterior) {
                    sonidoHover.play();  // Solo cuando cambia
                    indiceConfirmacionAnterior = i;
                }
                opcionesConfirmacion[i]->Play("on");
                indiceConfirmacion = i;
            }
            else {
                opcionesConfirmacion[i]->Play("off");
            }
        }

        // Si el mouse no está sobre ninguna opción, reiniciar
        if (hoverConfirmacion == -1) {
            indiceConfirmacionAnterior = -1;
        }
    }else {
    
        int hover = indiceOpcionHover();

        for (size_t i = 0; i < opciones.size(); ++i) {
            opciones[i]->Update();

            if ((int)i == hover) {
                if ((int)i != indiceHoverAnterior) {
                    sonidoHover.play();
                    opciones[i]->Play("on");
                    indiceHoverAnterior = i;
                }
                indiceSeleccionado = i;
            }
            else {
                opciones[i]->Play("off");
            }
        }

        if (hover == -1) {
            indiceHoverAnterior = -1;
        }
    }

}

bool Menu::requiereConfirmacion(Opciones accion) {
    return find(accionesQueRequierenConfirmacion.begin(), accionesQueRequierenConfirmacion.end(), accion) != accionesQueRequierenConfirmacion.end();

}
Opciones Menu::ejecutarOpcion(int i) {
    if (i >= 0 && i < opcionesDisponibles.size())
        return opcionesDisponibles[i];
    return Opciones::Ninguna;
}

int Menu::indiceOpcionHover() {
    for (int i = 0; i < opciones.size(); ++i) {
        if (opciones[i]->getGlobalBounds().contains(mouse.verPosition()))
            return i;
    }
    return -1;
}
int Menu::indiceConfirmacionHover() {
    for (int i = 0; i < 2; ++i) {
        if (opcionesConfirmacion[i]->getGlobalBounds().contains(mouse.verPosition()))
            return i;
    }
    return -1;
}

RenderWindow& Menu::verVentana() { return ventana; }

void Menu::mostrarConfirmacion(bool mostrar)
{
    mostrandoConfirmacion = mostrar;
}

bool Menu::mostreConfirmacion()
{
    return mostrandoConfirmacion;
}

