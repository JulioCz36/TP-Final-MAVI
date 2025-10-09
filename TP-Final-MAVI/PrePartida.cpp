#include "PrePartida.h"
PrePartida::PrePartida(RenderWindow& v) : Menu(v), barra("assets/UI/barra_espaciadora.png", true, 52, 8), mouse("assets/UI/clip_boton_subir.png", true, 35.5, 20) {
	cartel.cargarImagen("assets/UI/instrucciones.png");
	cartel.quePosition(128 / 2, 120);

	barra.Add("precion", { 0,1,2,3 }, 5, true);
	barra.setPosition(cartel.verPosition().x - 25, cartel.verPosition().y - 20);

	mouse.Add("precion", { 0,1,2,3 }, 5, true);
	mouse.setPosition(cartel.verPosition().x + 30, cartel.verPosition().y - 20);

	crearBoton("assets/UI/comenzar_ui.png", Opciones::IniciarPartida, 18, 7, 2.f, cartel.verPosition().x + cartel.verGlobalBounds().width / 2 - 18, cartel.verPosition().y + cartel.verGlobalBounds().height / 2 + 15);
}

void PrePartida::procesoEventos(Juego& j, Event& event) {
	procesoEventosMenu(j, event);
}

void PrePartida::actualizar(Juego& j) {
	actualizarMenu();
	barra.Update();
	mouse.Update();
}

void PrePartida::dibujar(RenderTarget& target) {
	dibujarMenu(target);
	cartel.dibujar(target);
	target.draw(barra);
	target.draw(mouse);
}