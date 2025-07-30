#pragma once
#include "Habilidad.h"
#include "Rapidez.h"

using namespace sf;
using namespace std;

class Mirage : public Nave {

public:
	Mirage();

	void habilidadNave() override;
};

