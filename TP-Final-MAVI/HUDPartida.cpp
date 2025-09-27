#include "HUDPartida.h"
HUDPartida::HUDPartida(int vidaMax_) : digito("assets/hud/numeros_sheet.png", true, 19, 19), vidaMax(vidaMax_) {
    for (int i = 0; i < 11; ++i) {
        digito.Add(to_string(i), { i }, 1, true);
    }
    digito.setScale(1.5, 1.5);

    //Vida
    icon_vidas.resize(vidaMax);
    for (int i = 0; i < vidaMax; i++) {
        icon_vidas[i].cargarImagen("assets/UI/vida_ui.png");
		icon_vidas[i].queEscala(1.5, 1.5);
        icon_vidas[i].quePosition(15 + (i * 1.2) * (icon_vidas[i].verGlobalBounds().width), 15);
    }
}

void HUDPartida::actualizar(int vida_t, int kilometros_t) {
    actualizarDigitos(kilometros, kilometros_t, 1250, 30, false);

    for (int i = 0; i < vidaMax; i++) {
        icon_vidas[i].esVisible(i < vida_t);
    }
}
void HUDPartida::dibujar(RenderTarget& window) {
    for (auto& k : kilometros) {
        window.draw(k);
    }

    for (auto& v : icon_vidas) {
        v.dibujar(window);
    }
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



