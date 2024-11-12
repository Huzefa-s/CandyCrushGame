#ifndef GAME_H
#define GAME_H

#include "Board.h"
#include "Player.h"

class Game {
public:
    Game(int maxMoves);
    void run();

private:
    Board board;
    Player player;
    int maxMoves;

    void update();
    void render();
    bool isGameOver();
};

#endif
