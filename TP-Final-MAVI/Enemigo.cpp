#include "Enemigo.h"
#include "utils.h"
#include "Partida.h"

Enemigo::Enemigo(const string& texture, int width, int height, initializer_list<int>idle, initializer_list<int>shot, initializer_list<int>destroyed, float vel, int hp, float cadencia, int queBala)
    : enemigo(texture,true, width, height), velocidad(vel), vida(hp), cadenciaDisparo(cadencia), danio(queBala) {

    enemigo.Add("idle", idle, 1, true);
    enemigo.Add("shot", shot,  60, false);
    enemigo.Add("destroyed", destroyed, 20, false);
    enemigo.setPosition(rand() % (1280 - ( width * 2)), + height / 2.f);
    enemigo.Play("idle");

    sonidoDisparo.cargar("assets/sonidos/shot.wav");
    sonidoDisparo.queVolumen(55);
}

Enemigo::Enemigo(Partida* p, const string& texture, int frameWidth, int frameHeight,initializer_list<int> idle, initializer_list<int> shot, initializer_list<int> destroyed, float vel, int hp, float cadencia, int queBala)
    : Enemigo(texture, frameWidth, frameHeight, idle, shot, destroyed, vel, hp, cadencia, queBala){

    partida = p;
}

void Enemigo::actualizar(float deltaTime) {
    if (!destruido) {
        comportamiento(deltaTime);
        if (puedeDisparar()) {
            disparar();
        }
    }
    actualizarAnimacion();
};
void Enemigo::dibujar(RenderWindow& window) {
    window.draw(enemigo);
}

void Enemigo::actualizarAnimacion() {
    enemigo.Update();
    if (enemigo.IsFinished("shot") && !enemigo.IsPlaying("destroyed")) {
        enemigo.Play("idle");
    }
    if (vida <= 0 && !enemigo.IsPlaying("destroyed") && !enemigo.IsFinished("destroyed")) {
        enemigo.Play("destroyed");
    }
}

bool Enemigo::colisionaCon(const FloatRect& objeto) {return enemigo.getGlobalBounds().intersects(objeto);}
bool Enemigo::estaMuerto() { return vida <= 0 && enemigo.IsFinished("destroyed"); }
bool Enemigo::fueDestruido() const { return destruido; }

void Enemigo::destruir(){
    if (!destruido) {
        vida = 0;
        destruido = true;
        enemigo.Play("destroyed");
    }
}
void Enemigo::recibirDanio(int dmg) {
    vida -= dmg;
    if (vida <= 0) {
        destruir();
    }
}


bool Enemigo::puedeDisparar() {return !enemigo.IsPlaying("destroyed") && relojDisparo.verTiempoTranscurrido() >= cadenciaDisparo; }
void Enemigo::disparar() {
    if (cadenciaDisparo <= 0.f) return;

    relojDisparo.reiniciar();

    sonidoDisparo.play();
    enemigo.Play("shot");

    // Dirección normalizada 
    Vector2f dirNormal = normalizar(verDireccionDisparo());

    float distanciaCabeza = enemigo.getGlobalBounds().height / 2.f;

    // Posición final para disparo
    Vector2f bulletPosition = enemigo.getPosition() + dirNormal * distanciaCabeza;

    partida->agregarLasersEnemigos(make_unique<Bala>(danio, bulletPosition, dirNormal,false));
}

FloatRect Enemigo::verBounds() {return enemigo.getGlobalBounds();}
bool  Enemigo::estaFueraDePantalla() {
    Vector2f pos = enemigo.getPosition();
    if (pos.y > 720) {
        return true;
    }
    return false;
}
Vector2f Enemigo::verPosition() {return enemigo.getPosition();}
void Enemigo::quePosition(Vector2f pos) {enemigo.setPosition(pos.x, pos.y);}
void Enemigo::queAngle(float angulo) {enemigo.setRotation(angulo);}
void Enemigo::mover(Vector2f movimiento) {enemigo.move(movimiento.x, movimiento.y);}

float Enemigo::verDanoColision() { return danoColision; }
Vector2f Enemigo::verDireccionDisparo() const { return Vector2f(0.f, 1.f); }

