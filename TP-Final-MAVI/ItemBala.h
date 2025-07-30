#pragma once
#include "Item.h"
#include "Nave.h"
using namespace sf;
using namespace std;
class ItemBala : public Item {
    int bala, cant_balas;
    string texturePath;
public:
    ItemBala(int n_bala);
    void aplicarEfecto(Nave& nave) override;
};

