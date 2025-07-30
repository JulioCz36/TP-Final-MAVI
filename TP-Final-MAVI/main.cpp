#include <SFML/Graphics.hpp>

#include "Juego.h"

using namespace sf;

int main() {

    srand(static_cast<unsigned>(time(0)));
    Juego j;
    j.jugar();

    return 0;
}
