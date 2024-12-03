#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include "Board.h"

class Game {
public:
    Game();
    void run();

private:
    void processEvents();
    void update();
    void draw();
    void drawStartScreen();
    void drawGameOverScreen();
    void resetGame();

    sf::RenderWindow app;
    sf::Texture tBackground, tcandy, tspecialCandy;
    sf::Sprite background, candy, specialCandy;
    sf::Font Font;
    sf::Text scoreText, movesText, startScreenText, levelText; // Single declaration for all text elements
    sf::Text finalScoreText; // Displays the final score

    Board board;
    int click, x0, y0, x, y;
    bool isSwap, isMoving;
    int score;
    int movesLeft;
    int selectedLevel; // Track the selected level
    int gameState;     // 0 = Start Screen, 1 = Playing, 2 = Game Over
    bool isGameOver;         // Tracks if the game is over
    
};

#endif 
