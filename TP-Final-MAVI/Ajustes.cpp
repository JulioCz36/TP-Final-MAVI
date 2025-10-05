#include "Ajustes.h"

Ajustes::Ajustes(RenderWindow& v) : Menu(v){

	titulo.cargarImagen("assets/UI/titulo_ajustes.png");
	titulo.queEscala(3.f, 3.f);
	titulo.quePosition(128 / 2, 50);

	cartel.cargarImagen("assets/UI/creditos.png");
	cartel.quePosition(128 / 2, 150);

	crearBoton("assets/UI/volver_ui.png", Opciones::SalirDeAjustes, 27, 8, 2.f, cartel.verPosition().x - cartel.verGlobalBounds().width / 2 + 27, cartel.verPosition().y + cartel.verGlobalBounds().height/ 2 + 20);
	crearBoton("assets/UI/sonido_trigger.png", Opciones::VolverAlMenu, 18, 8, 3.f, 128 / 2, cartel.verPosition().y - cartel.verGlobalBounds().height / 2 - 25);
}

void Ajustes::procesoEventos(Juego& j, Event& event){
	procesoEventosMenu(j, event);
}

void Ajustes::actualizar(Juego& j){
	actualizarMenu();
}

void Ajustes::dibujar(RenderTarget& target){
	dibujarMenu(target);
	cartel.dibujar(target);
	titulo.dibujar(target);
}
