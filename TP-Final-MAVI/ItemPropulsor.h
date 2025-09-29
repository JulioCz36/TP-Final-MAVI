#pragma once
#include "Item.h"
#include "Nave.h"

class ItemPropulsor : public Item {
public:
    ItemPropulsor(const Vector2f& pos);
    void aplicarEfecto(Nave& nave) override;
};

