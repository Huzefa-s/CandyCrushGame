#include "Board.h"
#include <cstdlib>
#include <ctime>

Board::Board() {
    
    for (int i = 1; i <= 8; i++) {
        for (int j = 1; j <= 8; j++) {
            grid[i][j].type = rand() % 6;
            grid[i][j].setPosition(j, i);
            if (i >= 6) {
                grid[i][j].isLocked = true;
            }
        }
    }
}

Candy& Board::getCandy(int row, int col) {
    return grid[row][col];
}

void Board::swapCandies(Candy& p1, Candy& p2) {
    std::swap(p1.col, p2.col);
    std::swap(p1.row, p2.row);
    std::swap(grid[p1.row][p1.col], grid[p2.row][p2.col]);
}

void Board::findMatches() {
    for (int i = 1; i <= 8; i++) {
        for (int j = 1; j <= 8; j++) {
            if (grid[i][j].type == grid[i + 1][j].type && grid[i][j].type == grid[i - 1][j].type) {
                for (int n = -1; n <= 1; n++) {
                    grid[i + n][j].match++;
                }
            }
            if (grid[i][j].type == grid[i][j + 1].type && grid[i][j].type == grid[i][j - 1].type) {
                for (int n = -1; n <= 1; n++) {
                    grid[i][j + n].match++;
                }
            }
        }
    }

    for (int i = 1; i <= 8; i++) {
        for (int j = 1; j <= 8; j++) {
            if (grid[i][j].isSpecial && grid[i][j].match > 0) {
                clearRowAndColumn(i, j);
            }
        }
    }
}

void Board::clearRowAndColumn(int row, int col) {
    for (int j = 1; j <= 8; j++) {
        grid[row][j].match++;  // Mark as matched to be destroyed
    }

    for (int i = 1; i <= 8; i++) {
        grid[i][col].match++;   // Mark as matched to be destroyed
    }
}


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

int Board::getScore() {
    int score = 0;
    for (int i = 1; i <= 8; i++) {
        for (int j = 1; j <= 8; j++) {
            score += grid[i][j].match;
        }
    }
    return score;
}

void Board::reset() {
    initializeBoard();
}

void Board::initializeBoard() {
    for (int i = 1; i <= 8; i++) {
        for (int j = 1; j <= 8; j++) {
            grid[i][j].row = i;
            grid[i][j].col = j;
            grid[i][j].type = rand() % 6; // Randomize candy type (assuming 6 types of candies)
            grid[i][j].isSpecial = (rand() % 10 == 0); 
            grid[i][j].match = 0;
            grid[i][j].fade = 255; // Reset fade effect
            
            // Mark the last two rows as locked
            if (i >= 6) {
                grid[i][j].isLocked = true;
            
            }
        }
    }
}


void Board::draw(sf::RenderWindow& app, sf::Sprite& regularCandySprite, sf::Sprite& specialCandySprite) {
    sf::Vector2i offset(48, 24);
    for (int i = 1; i < 8; i++) { // Iterating through grid positions
        for (int j = 1; j < 8; j++) {
            Candy& p = grid[i][j];

            // Set positions for regular and special candies
            regularCandySprite.setPosition(p.x, p.y);
            specialCandySprite.setPosition(p.x, p.y);

            // Check if candy is locked
            if (p.isLocked) {
                // Apply black color tint for locked candies
                if (p.isSpecial) {  // Special locked candy logic
                    sf::IntRect specialRect(p.type * 50, 0, 50, 50); // Assuming 50x50 size per candy
                    specialCandySprite.setTextureRect(specialRect);
                    specialCandySprite.setColor(sf::Color::Black);  // Apply black tint
                    app.draw(specialCandySprite);  // Draw special locked candy
                } else {  // Regular locked candy logic
                    sf::IntRect regularRect(p.type * 50, 0, 50, 50); // Assuming 50x50 size per candy
                    regularCandySprite.setTextureRect(regularRect);
                    regularCandySprite.setColor(sf::Color::Black);  // Apply black tint
                    app.draw(regularCandySprite);  // Draw regular locked candy
                }
            } else {
                // Normal drawing logic for unlocked candies
                if (p.isSpecial) {  // Special candy logic
                    sf::IntRect specialRect(p.type * 50, 0, 50, 50); // Assuming 50x50 size per candy
                    specialCandySprite.setTextureRect(specialRect);
                    specialCandySprite.setColor(sf::Color(255, 255, 255, p.fade));  // Apply fade effect
                    app.draw(specialCandySprite);  // Draw special candy
                } else {  // Regular candy logic
                    sf::IntRect regularRect(p.type * 50, 0, 50, 50); // Assuming 50x50 size per candy
                    regularCandySprite.setTextureRect(regularRect);
                    regularCandySprite.setColor(sf::Color(255, 255, 255, p.fade));  // Apply fade effect
                    app.draw(regularCandySprite);  // Draw regular candy
                }
            }
        }
    }
}


void Board::unlockTiles() {
    for (int i = 6; i <= 8; i++) {  // Last two rows
        for (int j = 1; j <= 8; j++) {
            // Check for adjacent cleared candies
            if (i > 1 && !grid[i - 1][j].isLocked && grid[i - 1][j].match > 0) {
                grid[i][j].isLocked = false;  // Unlock tile
            }
            if (i < 8 && !grid[i + 1][j].isLocked && grid[i + 1][j].match > 0) {
                grid[i][j].isLocked = false;  // Unlock tile
            }
            if (j > 1 && !grid[i][j - 1].isLocked && grid[i][j - 1].match > 0) {
                grid[i][j].isLocked = false;  // Unlock tile
            }
            if (j < 8 && !grid[i][j + 1].isLocked && grid[i][j + 1].match > 0) {
                grid[i][j].isLocked = false;  // Unlock tile
            }
        }
    }
}

