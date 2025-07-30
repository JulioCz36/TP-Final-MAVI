#pragma once
#include "Item.h"
#include "Nave.h"
using namespace sf;
using namespace std;

class ItemPuntos : public Item {
public:
    ItemPuntos();
    bool mostrarEnHUD()override;
    void aplicarEfecto(Nave& nave) override;
};

