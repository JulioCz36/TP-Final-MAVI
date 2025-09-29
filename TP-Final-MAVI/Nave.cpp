#include "Nave.h"
#include "Partida.h"

Nave::Nave(float x, float y, float fuerza, int vida) :destruccion("assets/Jugador/nave_destruida.png", true,8, 8),
propulsor("assets/Jugador/propulsor.png",true,8,8), escudo("assets/Jugador/escudo.png", true, 16, 16),fuerzaSalto(-fuerza), vidaMaxima(vida){

	vidaActual = vidaMaxima;

	nave.cargarImagen("assets/Jugador/nave.png");
    nave.quePosition(x, y);

    propulsor.Add("propulsor1", { 0,1,2,3 }, 6, true);
    propulsor.setPosition(nave.verPosition().x, nave.verPosition().y);
    propulsor.Add("propulsor2", { 4,5,6,7 }, 6, true);
    
    destruccion.setScale(2, 2);
    destruccion.Add("destruccion", { 0,1,2,3,4,5 }, 8, false);

	escudo.setScale(2, 2);
    escudo.Add("desplegando", { 0,1,2,3 }, 6, false);
    escudo.Add("acticvado", { 3 }, 6, true);
    escudo.Add("desactivando", { 3,2,1,0 }, 6, false);

    //hurtbox personalizada;
    tam_central = { 6, 15 };
    tam_superior = { 15, 11 };
    offsetYSuperior = 3;

    //hibox para el escudo
    radioHitbox = 16;
}

void Nave::recibirDano(float dano) {
    if (!invulnerable) vidaActual -= dano;

    if (vidaActual <= 0) {
        vidaActual = 0;
        iniciarDestruccion();
    }
}
float Nave::verVida(){return vidaActual;}
float Nave::verVidaMax() { return vidaMaxima; }
void Nave::aumentarVida(int canVida) {
    if (vidaActual < vidaMaxima) {
        vidaActual += canVida;
        if (vidaActual > vidaMaxima) {
            vidaActual = vidaMaxima;
        }
    }
}

Vector2f  Nave::verPos() {return nave.verPosition();}

void Nave::actualizar(float deltaTime) {
    if (enDestruccion) {
        destruccion.Update();
        return;
    }

    if (esperando) return;

    if (propulsorActivo) {
        if (!propulsor.IsPlaying("propulsor2")) {
            propulsor.Play("propulsor2");
        }
        nave.mover(0, velY * deltaTime);

        if (relojPropulsor.verTiempoTranscurrido() >= duracionPropulsor) {
            invulnerable = false;
            propulsorActivo = false;
        }
    }
    else {
        velY += gravedad * deltaTime; // v = v0 + a*t
        nave.mover(0, velY * deltaTime); // y = y0 + v*t
    }

    propulsor.setPosition(nave.verPosition().x, nave.verPosition().y + 9);
    propulsor.Update();

    if (escudoActivo) {
        escudo.setPosition(nave.verPosition());
        escudo.Update();

        if (escudo.IsFinished("desplegando") && !escudoDesactivandose) {
            escudo.Play("acticvado");
            usarHitboxCircular = true;
            invulnerable = true;
        }
        //hago que parpadee cuando queda poco
        if (!escudoDesactivandose && relojEscudo.verTiempoTranscurrido() >= duracionEscudo - 2.f) {
            int t = static_cast<int>(relojEscudo.verTiempoTranscurrido() * 10);
            if (t % 2 == 0) escudo.setColor(Color(255, 255, 255, 128));
            else escudo.setColor(Color::White);
        }
        else {
            escudo.setColor(Color::White);
        }

        if (relojEscudo.verTiempoTranscurrido() >= duracionEscudo && !escudoDesactivandose) {
            escudoDesactivandose = true;
            escudo.Play("desactivando");
            usarHitboxCircular = false;
            invulnerable = false;
        }
        if (escudoDesactivandose && escudo.IsFinished("desactivando")) {
            escudoActivo = false;
            escudoDesactivandose = false;
        }
    }

    if (!saltando) {
        float distanciaCaida = nave.verPosition().y - alturaInicioCaida;
        if (distanciaCaida > limiteCaida) {
            iniciarDestruccion();
        }
    }
}
void Nave::manejarEventos(Event& e) {
    if (propulsorActivo) return;

    if (e.type == Event::KeyPressed && e.key.code == salto) {
        if (esperando) esperando = false;
        velY = fuerzaSalto; // impulso inicial hacia arriba
        saltando = true;
        propulsor.Play("propulsor1");
    }
    if (e.type == Event::KeyReleased && e.key.code == Keyboard::Space) {
        saltando = false;
        alturaInicioCaida = nave.verPosition().y;
    }
}
void Nave::dibujar(RenderTarget& w) {
    if (enDestruccion) {
        w.draw(destruccion);
    }
    else {
        nave.dibujar(w);
        if (saltando || propulsorActivo) w.draw(propulsor);

        if (escudoActivo) {
            w.draw(escudo);
        }

        dibujarBox(w);
    }
}

void Nave::iniciarDestruccion() {
    if (!enDestruccion) {
        enDestruccion = true;
        velY = 0;         
        gravedad = 0;      
        destruccion.setPosition(nave.verPosition());
        destruccion.Play("destruccion");
    }
}
bool Nave::estaEnDestruccion() {return enDestruccion;}
bool Nave::estaMuerto() {return destruccion.IsFinished("destruccion");}

void Nave::activarEscudo(float segundos) {
    if (!escudoActivo && !escudoDesactivandose) {
        escudo.setPosition(nave.verPosition());

        escudoActivo = true;
        escudoDesactivandose = false;

        duracionEscudo = segundos;  

        escudo.Play("desplegando");
        relojEscudo.reiniciar();
    }
}
bool Nave::estaConEscudo() {
    return escudoActivo;
}
void Nave::activarPropulsor(float segundos, float velocidadExtra) {
    if (!propulsorActivo) {
        propulsorActivo = true;
        invulnerable = true;
        duracionPropulsor = segundos;
        relojPropulsor.reiniciar();

        // anulamos controles
        saltando = false;
        velY = -velocidadExtra;
    }
}
bool Nave::estaConPropulsor() {
    return propulsorActivo;
}

float clamp(float val, float minVal, float maxVal) {
    return std::max(minVal, std::min(val, maxVal));
}

bool Nave::colisionaCon(const FloatRect& otro) {
    if (usarHitboxCircular) {
        Vector2f centro = verPos();
        centro.y += 0;

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
void Nave::dibujarBox(RenderTarget& w) {
    if (usarHitboxCircular) {
        Vector2f centro = nave.verPosition();
        centro.y += 0;

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

void Nave::pausar() {
    relojEscudo.pausar();
}
void Nave::reanudar() {
    relojEscudo.reanudar();
}

void Nave::setPartida(Partida* p) { partida = p; };

