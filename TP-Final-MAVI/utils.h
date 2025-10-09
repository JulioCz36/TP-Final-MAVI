#pragma once
#include <SFML/System/Vector2.hpp>
#include <corecrt_math.h>
using namespace sf;

inline Vector2f normalizar(const Vector2f& v) {
    float magnitud = sqrt(v.x * v.x + v.y * v.y);
    if (magnitud != 0)
        return Vector2f(v.x / magnitud, v.y / magnitud);
    else
        return Vector2f(0.f, 0.f);
}

enum class Opciones {
	Ninguna,
	Comenzar,
	IniciarPartida,
	ComoJugar,
	Continuar,
	Reiniciar,
	VolverAlMenu,
	SalirDelJuego,
	Ajustes,
	SalirDeAjustes,
};


