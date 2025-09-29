#pragma once
#include "Item.h"
#include "Nave.h"
using namespace sf;
using namespace std;

class ItemVida : public Item {
public:
	ItemVida(const Vector2f& pos);
	void aplicarEfecto(Nave& nave) override;
};

