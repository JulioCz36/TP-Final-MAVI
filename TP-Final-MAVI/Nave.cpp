#include "Nave.h"
#include "Partida.h"

Nave::Nave(float x, float y, float fuerza, int resi) :destruccion("assets/Jugador/nave_destruida.png", true,8, 8),
propulsor("assets/Jugador/propulsor.png",true,8,8), fuerzaSalto(-fuerza), resistencia(resi), resistenciaMaxima(resi){

	nave.cargarImagen("assets/Jugador/nave.png");
    nave.quePosition(x, y);

    propulsor.Add("propulsor1", { 0,1,2,3 }, 6, true);
    propulsor.setPosition(nave.verPosition().x, nave.verPosition().y);
    propulsor.Add("propulsor2", { 4,5,6,7 }, 6, true);
    
    destruccion.Add("destruccion", { 0,1,2,3 }, 8, false);

    //hurtbox en personalizada;
    tam_central = { 20, 75 };
    tam_superior = { 99, 30 };
    offsetYSuperior = 30;
}

void Nave::recibirDano(float dano) {
    resistencia -= dano;
    if (resistencia <= 0) {
        iniciarDestruccion();
    }
}
float Nave::verVida(){return resistencia;}
void Nave::aumentarVida(int canVida) {
    if (resistencia < resistenciaMaxima) {
        resistencia += canVida;
        if (resistencia > resistenciaMaxima) {
            resistencia = resistenciaMaxima;
        }
    }
}
bool Nave::esInvulnerable() {return invulnerable;}
void Nave::activarInvulnerabilidad(float segundos) {
    invulnerable = true;
    duracionInvulnerabilidad = segundos;
    relojInvulnerabilidad.reiniciar();
}


void Nave::setPartida(Partida* p) { partida = p; };

Vector2f  Nave::verPos() {return nave.verPosition();}
bool Nave::estaQuieto() {
    return !(Keyboard::isKeyPressed(salto));
}
void Nave::verificarLimitesPantalla() {
    FloatRect bounds = nave.verGlobalBounds();
    //aca la pantalla es de 128x256
    if (nave.verPosition().x - bounds.width / 2 < 0) {
        nave.quePosition(bounds.width / 2, nave.verPosition().y);
    }
    if (nave.verPosition().x + bounds.width / 2 > 128) {
        nave.quePosition(128 - bounds.width / 2, nave.verPosition().y);
    }
}

void Nave::actualizar(float deltaTime) {
    if (enDestruccion) {
        destruccion.Update();
        if (destruccion.IsFinished("destruccion")) {
            resistencia = 0;
        }
        return;
    }

    if (esperando) {
        return;
    }

    velY += gravedad * deltaTime; // v = v0 + a*t
    nave.mover(0, velY * deltaTime); // y = y0 + v*t

    propulsor.setPosition(nave.verPosition().x, nave.verPosition().y + 9);
    propulsor.Update();

    if (!saltando) {
        float distanciaCaida = nave.verPosition().y - alturaInicioCaida;
        if (distanciaCaida > limiteCaida) {
            iniciarDestruccion();
        }
    }

    verificarLimitesPantalla();
}
void Nave::manejarEventos(Event& e) {
    if (e.type == Event::KeyPressed && e.key.code == salto) {
        if (esperando) esperando = false;
        velY = fuerzaSalto; // impulso inicial hacia arriba
        saltando = true;
        propulsor.Play("propulsor1");
    }
    if (e.type == Event::KeyReleased && e.key.code == Keyboard::Space) {
        saltando = false;
        alturaInicioCaida = nave.verPosition().y; // guardamos altura desde donde cae
    }
}
void Nave::dibujar(RenderTarget& w) {
    nave.dibujar(w);
    if(saltando)w.draw(propulsor);
    //dibujarHitbox(w);
}

void Nave::iniciarDestruccion() {
    if (!enDestruccion) {
        enDestruccion = true;
        destruccion.Play("destruccion");
    }
}
bool Nave::estaEnDestruccion() {return enDestruccion;}
bool Nave::estaMuerto() {return resistencia <= 0 && destruccion.IsFinished("destruccion");}


void Nave::pausar() {
    relojInvulnerabilidad.pausar();
}
void Nave::reanudar() {
    relojInvulnerabilidad.reanudar();
}

void Nave::configurarHitboxCircular(float radio, float offsetY) {
    radioHitbox = radio;
    offsetYHitboxCircular = offsetY;
}
void Nave::hitboxCircular(bool activar) {
    usarHitboxCircular = activar;
}

float clamp(float val, float minVal, float maxVal) {
    return std::max(minVal, std::min(val, maxVal));
}

bool Nave::colisionaCon(const FloatRect& otro) {
    if (usarHitboxCircular) {
        Vector2f centro = verPos();
        centro.y += offsetYHitboxCircular;

        float closestX = clamp(centro.x, otro.left, otro.left + otro.width);
        float closestY = clamp(centro.y, otro.top, otro.top + otro.height);

        float dx = centro.x - closestX;
        float dy = centro.y - closestY;

        return (dx * dx + dy * dy) <= (radioHitbox * radioHitbox);
    }
    else {
        FloatRect parteCentral(verPos().x - tam_central.x / 2, verPos().y - tam_central.y / 2, tam_central.x, tam_central.y);
        FloatRect parteSuperior(verPos().x - tam_superior.x / 2, verPos().y - tam_central.y / 2 + offsetYSuperior, tam_superior.x, tam_superior.y);
        return parteCentral.intersects(otro) || parteSuperior.intersects(otro);
    }
}
void Nave::dibujarHitbox(RenderWindow& w) {
    if (usarHitboxCircular) {
        Vector2f centro = nave.verPosition();
        centro.y += offsetYHitboxCircular;

        CircleShape circuloHitbox(radioHitbox);
        circuloHitbox.setOrigin(radioHitbox, radioHitbox);
        circuloHitbox.setPosition(centro);
        circuloHitbox.setFillColor(Color::Transparent);
        circuloHitbox.setOutlineColor(Color::Green);
        circuloHitbox.setOutlineThickness(1.f);
        w.draw(circuloHitbox);
    }
    else {
        Vector2f pos = nave.verPosition();

        FloatRect parteCentral(pos.x - tam_central.x / 2, pos.y - tam_central.y / 2, tam_central.x, tam_central.y);
        FloatRect parteSuperior(pos.x - tam_superior.x / 2, pos.y - tam_central.y / 2 + offsetYSuperior, tam_superior.x, tam_superior.y);

        RectangleShape debugCentral(Vector2f(parteCentral.width, parteCentral.height));
        debugCentral.setPosition(parteCentral.left, parteCentral.top);
        debugCentral.setFillColor(Color::Transparent);
        debugCentral.setOutlineColor(Color::Red);
        debugCentral.setOutlineThickness(1.f);
        w.draw(debugCentral);

        RectangleShape debugSuperior(Vector2f(parteSuperior.width, parteSuperior.height));
        debugSuperior.setPosition(parteSuperior.left, parteSuperior.top);
        debugSuperior.setFillColor(Color::Transparent);
        debugSuperior.setOutlineColor(Color::Blue);
        debugSuperior.setOutlineThickness(1.f);
        w.draw(debugSuperior);
    }
}



