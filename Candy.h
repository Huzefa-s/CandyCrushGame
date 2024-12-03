#ifndef CANDY_H
#define CANDY_H

#include <SFML/Graphics.hpp>
using namespace sf;

const int tileSize = 54;

class Candy {
public:
    int x, y;          // Screen position
    int col, row;      // Grid position
    int type;          // Candy type
    int match;         // Match counter
    int fade;         // Transparency (used for fading)
    bool isSpecial;
    bool isLocked;
    
    Candy();
    void setPosition(int col, int row);
};

#endif // CANDY_H
