#pragma once
#include "Item.h"
#include "Nave.h"
using namespace sf;
using namespace std;

class ItemVida : public Item {
public:
	ItemVida();
	void aplicarEfecto(Nave& nave) override;
};

