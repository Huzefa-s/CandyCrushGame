#include "Board.h"
#include <cstdlib>
#include <ctime>

//initializes board
Board::Board() {
    
    for (int i = 1; i <= 8; i++) {
        for (int j = 1; j <= 8; j++) {
            grid[i][j].type = rand() % 6;
            grid[i][j].setPosition(j, i);
            if (i >= 6 and i < 8) {
                grid[i][j].isLocked = true;
            }
        }
    }
}

//returns the position candy
Candy& Board::getCandy(int row, int col) {
    return grid[row][col];
}

//Swaps two candies
void Board::swapCandies(Candy& p1, Candy& p2) {
    std::swap(p1.col, p2.col);
    std::swap(p1.row, p2.row);
    std::swap(grid[p1.row][p1.col], grid[p2.row][p2.col]);
}


void Board::findMatches() {
    for (int i = 1; i <= 8; i++) {
        for (int j = 1; j <= 8; j++) {
            
            //Checks for vertival match
            if (grid[i][j].type == grid[i + 1][j].type && grid[i][j].type == grid[i - 1][j].type) {
                for (int n = -1; n <= 1; n++) {
                    grid[i + n][j].match++;
                }
            }

            //Checks for horizontal match
            if (grid[i][j].type == grid[i][j + 1].type && grid[i][j].type == grid[i][j - 1].type) {
                for (int n = -1; n <= 1; n++) {
                    grid[i][j + n].match++;
                }
            }
        }
    }
    //Checks for special candy
    for (int i = 1; i <= 8; i++) {
        for (int j = 1; j <= 8; j++) {
            if (grid[i][j].isSpecial && grid[i][j].match > 0) {
                clearRowAndColumn(i, j);
            }
        }
    }
}

//Effect of Special candy
void Board::clearRowAndColumn(int row, int col) {
    for (int j = 1; j <= 8; j++) {
        grid[row][j].match++;
    }

    for (int i = 1; i <= 8; i++) {
        grid[i][col].match++;
    }
}

//Falling mechanic and replaces candies after they are matched
void Board::updateBoard() {
     
    for (int i = 8; i > 0; i--) {
        for (int j = 1; j <= 8; j++) {
            if (grid[i][j].match) {
                for (int n = i; n > 0; n--) {
                    if (!grid[n][j].match) {
                        swapCandies(grid[n][j], grid[i][j]);
                        break;
                    }
                }
            }
        }
    }
    for (int j = 1; j <= 8; j++) {
        for (int i = 8, n = 0; i > 0; i--) {
            if (grid[i][j].match) {
                grid[i][j].type = rand() % 6;
                grid[i][j].y = -tileSize * n++;
                grid[i][j].match = 0;
                grid[i][j].fade = 255;
                grid[i][j].isSpecial = (rand() % 10 == 0);
            }
        }
    }
}

//returns current score
int Board::getScore() {
    int score = 0;
    for (int i = 1; i <= 8; i++) {
        for (int j = 1; j <= 8; j++) {
            score += grid[i][j].match;
        }
    }
    return score;
}

//resets board
void Board::reset() {
    initializeBoard();
}

//initialozes board after the 1st time
void Board::initializeBoard() {
    for (int i = 1; i <= 8; i++) {
        for (int j = 1; j <= 8; j++) {
            grid[i][j].row = i;
            grid[i][j].col = j;
            grid[i][j].type = rand() % 6; 
            grid[i][j].isSpecial = (rand() % 10 == 0); 
            grid[i][j].match = 0;
            grid[i][j].fade = 255;

            if (i >= 6 and i < 8) {
                grid[i][j].isLocked = true;
            
            }
        }
    }
}


void Board::draw(sf::RenderWindow& app, sf::Sprite& regularCandySprite, sf::Sprite& specialCandySprite) {
    sf::Vector2i offset(48, 24);
    for (int i = 1; i < 8; i++) { 
        for (int j = 1; j < 8; j++) {
            Candy& p = grid[i][j];

            regularCandySprite.setPosition(p.x, p.y);
            specialCandySprite.setPosition(p.x, p.y);
            //mechanic for locked tiles
            if (p.isLocked) {

                if (p.isSpecial) {  
                    sf::IntRect specialRect(p.type * 50, 0, 50, 50);
                    specialCandySprite.setTextureRect(specialRect);
                    specialCandySprite.setColor(sf::Color::Black);
                    app.draw(specialCandySprite); 
                } else {
                    sf::IntRect regularRect(p.type * 50, 0, 50, 50);
                    regularCandySprite.setTextureRect(regularRect);
                    regularCandySprite.setColor(sf::Color::Black); 
                    app.draw(regularCandySprite); 
                }
            } 
            //for normal tiles
            else {
                if (p.isSpecial) { 
                    sf::IntRect specialRect(p.type * 50, 0, 50, 50); 
                    specialCandySprite.setTextureRect(specialRect);
                    specialCandySprite.setColor(sf::Color(255, 255, 255, p.fade)); 
                    app.draw(specialCandySprite); 
                } else { 
                    sf::IntRect regularRect(p.type * 50, 0, 50, 50); 
                    regularCandySprite.setTextureRect(regularRect);
                    regularCandySprite.setColor(sf::Color(255, 255, 255, p.fade)); 
                    app.draw(regularCandySprite); 
                }
            }
        }
    }
}

//unlcoks locked tiles when match is made near them
void Board::unlockTiles() {
    for (int i = 1; i <= 8; i++) { 
        for (int j = 1; j <= 8; j++) {
            if (i > 1 && !grid[i - 1][j].isLocked && grid[i - 1][j].match > 0) {
                grid[i][j].isLocked = false;  
            }
            if (i < 8 && !grid[i + 1][j].isLocked && grid[i + 1][j].match > 0) {
                grid[i][j].isLocked = false; 
            }
            if (j > 1 && !grid[i][j - 1].isLocked && grid[i][j - 1].match > 0) {
                grid[i][j].isLocked = false;
            }
            if (j < 8 && !grid[i][j + 1].isLocked && grid[i][j + 1].match > 0) {
                grid[i][j].isLocked = false;
            }
        }
    }
}

