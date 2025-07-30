#include "Nave.h"
#include "Partida.h"

Nave::Nave(const string& texture,int vel, int resi)
    :nave(texture, true,99, 75), fire("assets/jugador/naves/fire_sheet.png",true,79,34), velocidad(vel), resistencia(resi), resistenciaMaxima(resi){
    nave.Add("idle", { 0 }, 1, true);
    nave.Add("destroyed", { 0 }, 60, false);

    nave.Add("double-idle", { 1 }, 1, true);
    nave.Add("shot", { 1,2,3,4,5,6,7,8,9 }, 60, false);
    nave.Add("double-destroyed", { 0 }, 60, false);

    nave.setPosition(640, 645);

    //Hibox en personalizada;
    tam_central = { 20, 75 };
    tam_superior = { 99, 30 };
    offsetYSuperior = 30;


    fire.Add("fire1", { 0,1,2,3,4 }, 6, true);
    fire.Add("fire2", { 5,6,7,8,9 }, 6, true);
    fire.setPosition(nave.getPosition().x, nave.getPosition().y);

    sonidoDisparo.cargar("assets/sonidos/shot.wav");
    sonidoDisparo.queVolumen(55);

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

Habilidad* Nave::queHabilidad() {return habilidad;}

void Nave::disparar() {
    Vector2f dir(0, -1);
    if (dobleDisparoActivo) {
        sonidoDisparo.play();
        Vector2f bulletPosition(nave.getPosition().x - 26, nave.getPosition().y - nave.getGlobalBounds().height / 2);
        partida->agregarLasersJugador(make_unique<Bala>(bala_n, bulletPosition, dir, true));

        Vector2f bulletPosition2(nave.getPosition().x + 26, nave.getPosition().y - nave.getGlobalBounds().height / 2);
        partida->agregarLasersJugador(make_unique<Bala>(bala_n, bulletPosition2, dir, true));

        balasEspeciales--;
        nave.Play("shot");
    }
    else {
        sonidoDisparo.play();
        Vector2f bulletPosition(nave.getPosition().x, nave.getPosition().y - nave.getGlobalBounds().height / 2 - 10);
        partida->agregarLasersJugador(make_unique<Bala>(bala_n, bulletPosition, dir,true));
        if (bala_n != 2) {
            balasEspeciales--;
        }
    }

    if (balasEspeciales <= 0) {
        bala_n = 2;
        if (dobleDisparoActivo) {
            doubleBalaNo();
        }
    }
}
void Nave::cambiarBalas(int n_bullet, int cantidad) {
    if (dobleDisparoActivo) {
        doubleBalaNo();
    }

    bala_n = n_bullet;
    balasEspeciales = cantidad;
}
int Nave::verCanBalas() {return balasEspeciales;}
void Nave::setPartida(Partida* p) { partida = p; };


void Nave::doubleBalaSi(int cantidad) {
    nave.Play("double-idle");
    bala_n = 2;
    dobleDisparoActivo = true;
    balasEspeciales = cantidad;
}
void Nave::doubleBalaNo() {
    nave.Play("idle");
    dobleDisparoActivo = false;
}

void Nave::mover(float deltaTime) {
    float desplazamiento = velocidad * deltaTime;

    if (Keyboard::isKeyPressed(der)) {
        nave.move(desplazamiento, 0);
    }
    if (Keyboard::isKeyPressed(izq)) {
        nave.move(-desplazamiento, 0);
    }
    if (Keyboard::isKeyPressed(acel)) {
        nave.move(0, -desplazamiento);
        actualizarAvance(true);
    } else {
        actualizarAvance(false);
    }
    if (Keyboard::isKeyPressed(retro)) {
        nave.move(0, desplazamiento);
    }
    fire.setPosition(nave.getPosition().x, nave.getPosition().y + 47);
}
void Nave::cambiarPos(float desplazamiento) {
    Vector2f pos = nave.getPosition();

    if (Keyboard::isKeyPressed(der)) {
        pos.x += desplazamiento;
    }
    if (Keyboard::isKeyPressed(izq)) {
        pos.x -= desplazamiento;
    }
    if (Keyboard::isKeyPressed(acel)) {
        pos.y -= desplazamiento;
    }
    if (Keyboard::isKeyPressed(retro)) {
        pos.y += desplazamiento;
    }

    nave.setPosition(pos.x, pos.y);

}
Vector2f  Nave::verPos() {return nave.getPosition();}
bool Nave::estaQuieto() {
    return !(Keyboard::isKeyPressed(der) ||
        Keyboard::isKeyPressed(izq) ||
        Keyboard::isKeyPressed(acel) ||
        Keyboard::isKeyPressed(retro));
}
void Nave::verificarLimitesPantalla() {
    FloatRect bounds = nave.getGlobalBounds();

    if (nave.getPosition().x - bounds.width / 2 < 0) {
        nave.setPosition(bounds.width / 2, nave.getPosition().y);
    }
    if (nave.getPosition().x + bounds.width / 2 > 1280) {
        nave.setPosition(1280 - bounds.width / 2, nave.getPosition().y);
    }
    if (nave.getPosition().y - bounds.height / 2 < 0) {
        nave.setPosition(nave.getPosition().x, bounds.height / 2);
    }
    if (nave.getPosition().y + bounds.height / 2 > 720) {
        nave.setPosition(nave.getPosition().x, 720 - bounds.height / 2);
    }
}


void Nave::actualizarAvance(bool avanzando) {
    if (avanzando) {
        fire.Play("fire2");
    }else {
        fire.Play("fire1");
    }
}
void Nave::esVisible(bool visible) {
    if (visible) {

        nave.setColor(Color(255, 255, 255, 255));
        fire.setColor(Color(255, 255, 255, 255));
    }
    else {
        nave.setColor(Color(255, 255, 255, 0));
        fire.setColor(Color(255, 255, 255, 0));
    }
}

void Nave::actualizar(float deltaTime) {
    if (!enDestruccion) {
        if (invulnerable && relojInvulnerabilidad.verTiempoTranscurrido() > duracionInvulnerabilidad) {
            invulnerable = false;
        }
        verificarLimitesPantalla();
        nave.Update();
        fire.Update();
        if (nave.IsFinished("shot")) {
            if (dobleDisparoActivo)
                nave.Play("double-idle");
        }
        mover(deltaTime);
    }
    else {
        nave.Update(); // animación de destrucción
        if (nave.IsFinished("destroyed") || nave.IsFinished("double-destroyed")) {
            resistencia = 0;
        }
    }
}
void Nave::manejarEventos(Event& e) {
    if (e.type == Event::KeyPressed && e.key.code == dis && puedeDisparar) {
        disparar();
        puedeDisparar = false;
    }
    if (e.type == Event::KeyReleased && e.key.code == dis) {
        puedeDisparar = true;
    }
    if (e.type == Event::KeyPressed && e.key.code == habi && habilidad->estaRecargada()) {
        habilidadNave();
    }
}
void Nave::dibujar(RenderWindow& w) {
    w.draw(nave);
    w.draw(fire);
    habilidad->dibujar(w);
    dibujarHitbox(w);
}

void Nave::iniciarDestruccion() {
    if (!enDestruccion) {
        enDestruccion = true;
        if (dobleDisparoActivo) {
            nave.Play("double-destroyed");
        }
        else {

            nave.Play("destroyed");
        }
    }
}
bool Nave::estaEnDestruccion() {return enDestruccion;}
bool Nave::estaMuerto() {return resistencia <= 0 && (nave.IsFinished("destroyed") || nave.IsFinished("double-destroyed"));}

void Nave::aumentarPuntos(int canPuntos) {puntos += canPuntos;}
int Nave::verPuntos(){return puntos;}

void Nave::pausar() {
    relojInvulnerabilidad.pausar();
    habilidad->pausar();
}
void Nave::reanudar() {
    relojInvulnerabilidad.reanudar();
    habilidad->reanudar();
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

        // Usar clamp para encontrar el punto más cercano del rectángulo al centro del círculo
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
        Vector2f centro = nave.getPosition();
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
        Vector2f pos = nave.getPosition();

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



