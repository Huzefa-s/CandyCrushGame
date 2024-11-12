#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include "Candy.h"

class Board {
public:
    Board(int rows, int cols);
    void initializeBoard(); // Sets up the initial board with random candies
    bool swap(int x1, int y1, int x2, int y2); // Swaps two candies
    bool checkMatch(); // Checks for matches of three or more candies
    void clearMatches(); // Clears matched candies
    void fillBoard(); // Fills empty spaces with new candies

private:
    int rows;
    int cols;
    std::vector<std::vector<Candy>> grid;

    bool isValidSwap(int x1, int y1, int x2, int y2); // Validates swaps
};

#endif // BOARD_H
