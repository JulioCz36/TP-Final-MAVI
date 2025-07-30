#pragma once
#include "Item.h"
#include "Nave.h"
using namespace sf;
using namespace std;

class ItemVida : public Item {
public:
	ItemVida();
	bool mostrarEnHUD()override;
	void aplicarEfecto(Nave& nave) override;
};

