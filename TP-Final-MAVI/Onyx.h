#pragma once
#include "Habilidad.h"
#include "Escudo.h"

using namespace sf;
using namespace std;

class Onyx : public Nave {

public:
	Onyx();

	void habilidadNave() override;
};

