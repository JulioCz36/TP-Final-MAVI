#include "Menu.h"
Menu::Menu(RenderWindow& v)
    : ventana(v) {
    fondo1.cargarImagen("assets/Fondo/fondo.png");
    fondo2.cargarImagen("assets/Fondo/fondo.png");

    fondo1.quePosition(128 / 2, 256 /2);
    fondo2.quePosition(128 / 2, fondo1.verPosition().y - fondo1.verGlobalBounds().height);

    sonidoDeFondo.cargar("assets/sonidos/sonido_menu.wav");
    sonidoDeFondo.queVolumen(25);
    sonidoHover.cargar("assets/sonidos/hover.wav");
    sonidoHover.queVolumen(20);

};

void Menu::procesoEventosMenu(Juego& j, Event& event) {
    if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {
        int hover = indiceOpcionHover();
        if (hover != -1) {
            accionPendiente = opcionesDisponibles[hover];
            ejecutarAccion(j, opcionesDisponibles[hover]);

        }
    }
}

void Menu::dibujarMenu(RenderTarget& target) {
    if (dibujarFondo) {
        fondo1.dibujar(target);
        fondo2.dibujar(target);
    }
    for (auto& opcion : opciones)
        target.draw(*opcion);
};
void Menu::actualizarMenu() {

    if (!sonidoDeFondo.estaReproduciendo()) {
        sonidoDeFondo.play();
    }

    float deltaTime = relojDeltaTime.verReinicio();
    actualizarFondo(deltaTime);
    actualizarAnimaciones();
}

void Menu::actualizarFondo(float deltaTime) {
    float altura = fondo1.verGlobalBounds().height;

    fondo1.mover(0, fondoVelocidad * deltaTime);
    fondo2.mover(0, fondoVelocidad * deltaTime);

    float borde1 = fondo1.verPosition().y + altura / 2.f;
    float borde2 = fondo2.verPosition().y + altura / 2.f;

    if (borde1 >= 256 *2) {
        fondo1.quePosition(fondo1.verPosition().x,fondo2.verPosition().y - altura);
    }
    if (borde2 >= 256 * 2) {
        fondo2.quePosition(fondo2.verPosition().x,fondo1.verPosition().y - altura);
    }
}

void Menu::dibujoFondo(bool fondo){
    dibujarFondo = fondo;
}
void Menu::actualizarAnimaciones() {
    int hover = indiceOpcionHover();
    for (size_t i = 0; i < opciones.size(); ++i) {
        opciones[i]->Update();

        if ((int)i == hover) {
            if ((int)i != indiceHoverAnterior) {
                sonidoHover.play();
                indiceHoverAnterior = i;
            }
            opciones[i]->Play("hover");
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

int Menu::indiceOpcionHover() {
    Vector2i pixelPos = Mouse::getPosition(ventana);

    // Transformar al mundo lógico (128x256)
    auto screenSize = ventana.getSize();
    float scaleX = static_cast<float>(screenSize.x) / 128.f;
    float scaleY = static_cast<float>(screenSize.y) / 256.f;
    float scale = std::min(scaleX, scaleY);

    float offsetX = (screenSize.x - 128.f * scale) / 2.f;
    float offsetY = (screenSize.y - 256.f * scale) / 2.f;

    Vector2f mousePos(
        (pixelPos.x - offsetX) / scale,
        (pixelPos.y - offsetY) / scale
    );

    for (int i = 0; i < (int)opciones.size(); ++i) {
        if (opciones[i]->getGlobalBounds().contains(mousePos))
            return i;
    }
    return -1;
}

void Menu::crearBoton(const string& ruta, Opciones tipo, float anchoFrame, float altoFrame, float escala, float posX, float posY) {
    auto opcion = make_shared<Afichmation>(ruta, true, anchoFrame, altoFrame);
    opcion->Add("off", { 0 }, 1, true);
    opcion->Add("hover", { 1 }, 1, true);
    opcion->setScale(escala, escala);
    opcion->setPosition(posX, posY);

    opciones.push_back(opcion);
    opcionesDisponibles.push_back(tipo);
}
void Menu::ejecutarAccion(Juego& j, Opciones accion) {
    switch (accion) {
    case Opciones::IniciarPartida:
        j.iniciarPartida();
        break;
    case Opciones::Comenzar:
        j.comenzar();
        break;
    case Opciones::ComoJugar:
        j.verInstrucciones();
        break;
    case Opciones::SalirDelJuego:
        j.salir();
        break;
    case Opciones::Continuar:
        j.reanudar();
        break;
    case Opciones::Reiniciar:
        j.reiniciar();
        break;
    case Opciones::VolverAlMenu:
        j.volverAlMenu();
        break;
    case Opciones::Ajustes:
        j.irAAjustes();
        break;
    case Opciones::SalirDeAjustes:
        j.salirDeAjustes();
        break;
    default:
        break;
    }
}