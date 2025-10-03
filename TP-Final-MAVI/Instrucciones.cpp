#include "Instrucciones.h"

Instrucciones::Instrucciones(RenderWindow& v) : Menu(v), barra("assets/UI/barra_espaciadora.png", true, 52, 8), mouse("assets/UI/clip_boton_subir.png", true, 35.5, 20) {
	crearBoton("assets/UI/casa_ui.png", Opciones::VolverAlMenu, 12, 13, 1.f, 15, 15);

	titulo.cargarImagen("assets/UI/titulo.png");
	titulo.queEscala(2.5, 2.5);
	titulo.quePosition(128 / 2, 60);

	cartel.cargarImagen("assets/UI/instrucciones.png");
	cartel.quePosition(128 / 2, 170);

	barra.Add("precion", { 0,1,2,3 }, 5, true);
	barra.setPosition(cartel.verPosition().x - 25, cartel.verPosition().y - 20);

	mouse.Add("precion", { 0,1,2,3 }, 5, true);
	mouse.setPosition(cartel.verPosition().x + 30, cartel.verPosition().y - 20);
}

void Instrucciones::procesoEventos(Juego& j, Event& event){
	procesoEventosMenu(j, event);
}

void Instrucciones::actualizar(Juego& j){
	actualizarMenu();
	barra.Update();
	mouse.Update();
}

void Instrucciones::dibujar(RenderTarget& target) {
	dibujarMenu(target);
	cartel.dibujar(target);
	target.draw(barra);
	target.draw(mouse);
	titulo.dibujar(target);

}
