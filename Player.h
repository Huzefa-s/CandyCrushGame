#ifndef PLAYER_H
#define PLAYER_H


class Player {
public:
    Player(int initialMoves);
    void addScore(int points);
    int getScore() const;
    void decreaseMove();
    int getMoves() const;

private:
    int score;
    int moves;
};

#endif
