#ifndef BOARD_H
#define BOARD_H

#include <SFML/Graphics.hpp>
#include "Candy.h"

class Board {
private:
    Candy grid[10][10];

public:
    Board();
    Candy& getCandy(int row, int col);
    void clearRowAndColumn(int row, int col);
    void swapCandies(Candy& p1, Candy& p2);
    void findMatches();
    void updateBoard();
    int getScore();
    void draw(sf::RenderWindow& app, sf::Sprite& regularCandySprite, sf::Sprite& specialCandySprite);
    void reset();
    void initializeBoard();
    void unlockTiles();
};

#endif // BOARD_H
