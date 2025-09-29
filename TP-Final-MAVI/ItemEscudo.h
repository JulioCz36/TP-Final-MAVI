#pragma once
#include "Item.h"
#include "Nave.h"
using namespace sf;

class ItemEscudo : public Item {
public:
    ItemEscudo(const Vector2f& pos);
    void aplicarEfecto(Nave& nave) override;
};