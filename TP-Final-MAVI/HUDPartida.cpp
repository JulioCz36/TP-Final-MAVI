#include "HUDPartida.h"
HUDPartida::HUDPartida(Habilidad* habi) : habilidad(habi), iconHabilidad(habilidad->verRutaTextura(),true, 91, 91), digito("assets/hud/numeros_sheet.png", true, 19, 19) {
    for (int i = 0; i < 11; ++i) {
        digito.Add(to_string(i), { i }, 1, true);
    }
    digito.setScale(1.5, 1.5);

    //Vida
    icon_vida.cargarImagen("assets/items/item_vida.png");
    icon_vida.quePosition(20 + icon_vida.verGlobalBounds().width, 660);

    for (int i = 0; i < 11; ++i) {
        int porcentaje = static_cast<int>((i / 6.f) * 100.f + 0.5f);
        string nombre = to_string(porcentaje) + "%";
        iconHabilidad.Add(nombre, {i},30,true);
    }
    iconHabilidad.setPosition(1280 - iconHabilidad.getGlobalBounds().width, 720 - iconHabilidad.getGlobalBounds().height);

    icon_item.cargarImagen("assets/items/item_vacio.png");
    icon_item.quePosition(iconHabilidad.getPosition().x - icon_item.verGlobalBounds().width * 1.8, 660);


    reciVidaBoss.cargarImagen("assets/boss/recipiente_vida.png");
    reciVidaBoss.quePosition(420,40);
    vidaBoss.cargarImagen("assets/boss/relleno_vida.png");
    vidaBoss.queOrigin(0, vidaBoss.verGlobalBounds().height / 2);
    vidaBoss.quePosition(reciVidaBoss.verPosition().x - vidaBoss.verGlobalBounds().width / 2, reciVidaBoss.verPosition().y);
}

void HUDPartida::actualizar(const string& itemActivo, int vida_t, int puntos_t, int cantidad) {


    actualizarDigitos(puntos, puntos_t, 1250, 30, false);
    actualizarDigitos(vida, vida_t, icon_vida.verPosition().x + 50, 660, true);

    if (!itemActivo.empty() && cantidad > 0) {
        icon_item.cargarImagen(itemActivo);
        actualizarDigitos(cantLasers, cantidad, icon_item.verPosition().x - 50, 660 ,false);

    }
    else {
        icon_item.cargarImagen("assets/items/item_vacio.png");
        cantLasers.clear();
    }

    habilidadActualizar();
}
void HUDPartida::dibujar(RenderWindow& window) {

    for (auto& p : puntos) {
        window.draw(p);
    }

    for (auto& v : vida) {
        window.draw(v);
    }
    icon_vida.dibujar(window);

    for (auto& cl : cantLasers) {
        window.draw(cl);
    }
    icon_item.dibujar(window);

    window.draw(iconHabilidad);

    if (mostrarBarraVidaBoss) {
        reciVidaBoss.dibujar(window);
        vidaBoss.dibujar(window);
    }
}

void HUDPartida::habilidadActualizar() {
    iconHabilidad.Update();
    float progreso = habilidad->recarga();

    int frameActual = static_cast<int>(progreso * 10.f + 0.5f); // de 0 a 10
    int porcentaje = static_cast<int>((frameActual / 6.f) * 100.f + 0.5f);

    std::string nombre = std::to_string(porcentaje) + "%";
    iconHabilidad.Play(nombre);

    habilidad->actualizar();
}
void HUDPartida::actualizarDigitos(vector<Afichmation>& destino, int valor, int posXFin, int posY, bool izquierdaADerecha) {
    destino.clear();
    string str = to_string(valor);
    float ancho = 19.f * digito.getScale().x;

    for (size_t i = 0; i < str.size(); ++i) {
        string nombre(1, str[i]);
        Afichmation nuevoDigito = digito;
        nuevoDigito.Play(nombre);

        int posX;
        if (izquierdaADerecha) {
            posX = posXFin + i * ancho;
        }
        else {
            posX = posXFin + (-ancho) * (str.size() - 1 - i);
        }

        nuevoDigito.setPosition(posX, posY);
        nuevoDigito.Update();
        destino.push_back(nuevoDigito);
    }
}

void HUDPartida::iniciarAnimacionVidaBoss() {
    barraVidaBossVisible = 0.f;
    animandoVidaBoss = true;
}
void HUDPartida::mostrarVidaBoss(bool verVida) {
    mostrarBarraVidaBoss = verVida;
}
void HUDPartida::actualizarAnimacionVidaBoss(float deltaTime, float vidaActual, float vidaMaxima) {
    if (animandoVidaBoss) {
        float velocidadLlenado = 5.f; // segundos para llenar la barra completa
        barraVidaBossVisible += deltaTime / velocidadLlenado;
        if (barraVidaBossVisible >= 1.f) {
            barraVidaBossVisible = 1.f;
            animandoVidaBoss = false;
        }
    }

    float escala = barraVidaBossVisible * (vidaActual / vidaMaxima);
    vidaBoss.queEscala(escala, 1.f);
}
bool HUDPartida::terminoAnimacionVidaBoss(){
    return mostrarBarraVidaBoss && !animandoVidaBoss;
}



