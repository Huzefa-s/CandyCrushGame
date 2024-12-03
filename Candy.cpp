#include "Candy.h"

Candy::Candy() : x(0), y(0), col(0), row(0), type(0), match(0), fade(255), isSpecial(false), isLocked(false) {}

//sets candy position
void Candy::setPosition(int col, int row) {
    this->col = col;
    this->row = row;
    x = col * tileSize;
    y = row * tileSize;
}
