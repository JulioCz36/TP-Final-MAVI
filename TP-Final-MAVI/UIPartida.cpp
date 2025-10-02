#include "UIPartida.h"
UIPartida::UIPartida(RenderWindow& v, Nave* j) : ventana(v), jugador(j) {
    botonSalto = make_shared<Afichmation>("assets/ui/salto_ui.png", true, 12, 13);

    botonSalto->Add("normal", { 0 }, 1, true);
    botonSalto->Add("hover", { 1 }, 1, true);
    botonSalto->Add("presionado", { 2 }, 1, true);

    botonSalto->setScale(3.f, 3.f);
    botonSalto->setPosition(64.7, 229.5);
    botonSalto->Play("normal");


	tablero.cargarImagen("assets/ui/tablero_salto.png");
    tablero.quePosition(128/2,231.5);
}

void UIPartida::manejarEventos(Event& e) {
    Vector2f mousePos = transformarMouse();

    if (botonSalto->getGlobalBounds().contains(mousePos)) {
        if (e.type == Event::MouseButtonPressed && e.mouseButton.button == Mouse::Left) {
            botonSalto->Play("presionado");
            jugador->iniciarSalto(); 
        }else {
            botonSalto->Play("hover");
        }
    }
    else {
        botonSalto->Play("normal");
    }

    if (e.type == Event::MouseButtonReleased && e.mouseButton.button == Mouse::Left) {
        jugador->finalizarSalto(); 
    }


}

void UIPartida::actualizar() {
    botonSalto->Update();
    Vector2f mousePos = transformarMouse();
    if (botonSalto->getGlobalBounds().contains(mousePos) && Mouse::isButtonPressed(Mouse::Left)) {
        jugador->mantenerSalto();
    }
}

void UIPartida::dibujar(RenderTarget& w) {
	tablero.dibujar(w);
    w.draw(*botonSalto);
}

Vector2f UIPartida::transformarMouse() {
    Vector2i pixelPos = Mouse::getPosition(ventana);
    auto screenSize = ventana.getSize();

    float scaleX = static_cast<float>(screenSize.x) / 128.f;
    float scaleY = static_cast<float>(screenSize.y) / 256.f;
    float scale = std::min(scaleX, scaleY);
    float offsetX = (screenSize.x - 128.f * scale) / 2.f;
    float offsetY = (screenSize.y - 256.f * scale) / 2.f;

    return Vector2f(
        (pixelPos.x - offsetX) / scale,
        (pixelPos.y - offsetY) / scale
    );
}
