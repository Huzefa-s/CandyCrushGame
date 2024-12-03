#include "Game.h"

Game::Game() 
    : app(sf::VideoMode(740, 480), "Candy Crush"), click(0), isSwap(false), isMoving(false), score(0), movesLeft(10), selectedLevel(0), gameState(0) {
    app.setFramerateLimit(60);
    tBackground.loadFromFile("images/background3.png");
    tcandy.loadFromFile("images/candies.png");
    tspecialCandy.loadFromFile("images/special.png");
    background.setTexture(tBackground);
    candy.setTexture(tcandy);
    specialCandy.setTexture(tspecialCandy);
    // Load font
    if (!Font.loadFromFile("fonts/arial.ttf")) {
        // Handle error loading font
    }

    // Initialize scoreText
    scoreText.setFont(Font);
    scoreText.setCharacterSize(24);
    scoreText.setFillColor(sf::Color::Black);
    scoreText.setPosition(app.getSize().x - 200, 10);

    // Initialize movesText
    movesText.setFont(Font);
    movesText.setCharacterSize(24);
    movesText.setFillColor(sf::Color::Black);
    movesText.setPosition(scoreText.getPosition().x+ 75, scoreText.getPosition().y + 30);


    // Initialize startScreenText
    startScreenText.setFont(Font);
    startScreenText.setCharacterSize(30);
    startScreenText.setFillColor(sf::Color::Black);
    startScreenText.setString("Select Level:\nPress 1, 2, or 3 to start");
    startScreenText.setPosition(app.getSize().x / 2 - startScreenText.getLocalBounds().width / 2, app.getSize().y / 2 - startScreenText.getLocalBounds().height / 2);

    // Initialize levelText
    levelText.setFont(Font);
    levelText.setCharacterSize(24);
    levelText.setFillColor(sf::Color::Black);
    levelText.setPosition(10, 40);

    // Initialize final score text
    finalScoreText.setFont(Font);
    finalScoreText.setCharacterSize(40);
    finalScoreText.setFillColor(sf::Color::Black);
    finalScoreText.setPosition(200.f, 200.f);
    finalScoreText.setString("");
}

void Game::run() {
    while (app.isOpen()) {
        processEvents();
        update();
        draw();
    }
}

void Game::processEvents() {
    sf::Event e;
    while (app.pollEvent(e)) {
        if (e.type == sf::Event::Closed) {
            app.close();
        }

        if (gameState == 0) { // Start Screen
            if (e.type == sf::Event::KeyPressed) {
                if (e.key.code == sf::Keyboard::Num1) {
                    selectedLevel = 1;
                    movesLeft = 10; // Set moves for level 1
                    gameState = 1; // Transition to Gameplay
                } else if (e.key.code == sf::Keyboard::Num2) {
                    selectedLevel = 2;
                    movesLeft = 15; // Set moves for level 2
                    gameState = 1; // Transition to Gameplay
                } else if (e.key.code == sf::Keyboard::Num3) {
                    selectedLevel = 3;
                    movesLeft = 20; // Set moves for level 3
                    gameState = 1; // Transition to Gameplay
                }
            }
        } else if (gameState == 1) { // Gameplay
            if (e.type == sf::Event::MouseButtonPressed && e.mouseButton.button == sf::Mouse::Left) {
                if (!isSwap && !isMoving) click++;
                sf::Vector2i pos = sf::Mouse::getPosition(app) - sf::Vector2i(48, 24);
                if (click == 1) {
                    x0 = pos.x / tileSize + 1;
                    y0 = pos.y / tileSize + 1;
                } else if (click == 2) {
                    x = pos.x / tileSize + 1;
                    y = pos.y / tileSize + 1;
                    if (abs(x - x0) + abs(y - y0) == 1) {
                        if (board.getCandy(y0, x0).isLocked || board.getCandy(y, x).isLocked) {
                            click = 0;
                        } else {
                            board.swapCandies(board.getCandy(y0, x0), board.getCandy(y, x));
                            isSwap = true;
                            click = 0;
                            movesLeft--;
                        }
                    } else {
                        click = 1;
                    }
                }
            }
        }
    }
}

void Game::update() {
     if (gameState == 1) { // Gameplay
        if (movesLeft <= 0) {
            // Transition to Game Over state
            finalScoreText.setString("Game Over!\nFinal Score: " + std::to_string(score));
            gameState = 2; // Move to Game Over state
            return;
        }

    int matchPoints = 0;

for (int i = 1; i <= 8; i++) {
    for (int j = 1; j <= 8; j++) {
        Candy& p = board.getCandy(i, j);
        if (p.match > 0) { // Check if there's a match
            // Assign points based on match size
            if (p.match == 3) matchPoints += 10;  // 3 candies = 10 points
            else if (p.match == 4) matchPoints += 20; // 4 candies = 20 points
            else if (p.match >= 5) matchPoints += 30; // 5+ candies = 30 points
        }
    }
}

    // Add the calculated points to the total score
    score += matchPoints;


    const int speed = 3;
    board.findMatches();
    isMoving = false;

    board.unlockTiles();

    for (int i = 1; i <= 8; i++) {
        for (int j = 1; j <= 8; j++) {
            Candy& p = board.getCandy(i, j);
            int dx = p.x - p.col * tileSize;
            int dy = p.y - p.row * tileSize;
            if (dx != 0) p.x -= std::min(abs(dx), speed) * (dx / abs(dx));
            if (dy != 0) p.y -= std::min(abs(dy), speed) * (dy / abs(dy));
            if (dx != 0 || dy != 0) isMoving = true;
        }
    }

    if (!isMoving) {
        for (int i = 1; i <= 8; i++) {
            for (int j = 1; j <= 8; j++) {
                Candy& p = board.getCandy(i, j);
                if (p.match && p.fade > 10) {
                    p.fade -= 10;
                    isMoving = true;
                }
            }
        }
    }

    if (isSwap && !isMoving) {
        if (board.getScore() == 0) board.swapCandies(board.getCandy(y0, x0), board.getCandy(y, x));
        isSwap = false;
    }

    if (!isMoving) board.updateBoard();}

    if (gameState == 2) { // Game Over
        // Wait 3 seconds and return to the start screen
        sf::sleep(sf::seconds(3));
        resetGame();
        gameState = 0; // Return to Start Screen
    }
}

void Game::draw() {
    app.clear();

    if (gameState == 0) { // Start Screen
        app.draw(background);
        app.draw(startScreenText);

    } else if (gameState == 1) { // Gameplay
        // Draw the game board and UI elements like score and moves
        app.draw(background);
        board.draw(app, candy, specialCandy);

        // Draw score and moves
        scoreText.setString("Score: " + std::to_string(score));
        scoreText.setPosition(app.getSize().x - scoreText.getLocalBounds().width - 10, 10);
        app.draw(scoreText);

        movesText.setString("Moves: " + std::to_string(movesLeft));
        //movesText.setPosition(10, 10);
        app.draw(movesText);
    } else if (gameState == 2) { // Game Over
        app.draw(background); 
        app.draw(finalScoreText); // Display the final score text
    }

    app.display();
}

void Game::drawStartScreen() {
    app.draw(background);
    app.draw(startScreenText);
}

void Game::drawGameOverScreen() {
    sf::Text gameOverText;
    gameOverText.setFont(Font);
    gameOverText.setString("Game Over!\nScore: " + std::to_string(score) + "\nReturning to Start Screen...");
    gameOverText.setCharacterSize(30);
    gameOverText.setFillColor(sf::Color::Red);
    gameOverText.setPosition(app.getSize().x / 2 - gameOverText.getLocalBounds().width / 2, app.getSize().y / 2 - gameOverText.getLocalBounds().height / 2);
    app.draw(gameOverText);

    // Wait for a few seconds, then reset to start screen
    sf::sleep(sf::seconds(3));

    resetGame(); // Reset game variables and board
    gameState = 0; // Return to Start Screen
}

void Game::resetGame() {
    // Reset all game variables
    score = 0;
    movesLeft = 10; // Or reset based on the selected level
    selectedLevel = 0;
    gameState = 0; // Go back to Start Screen

    // Reset board and update start screen message
    board.reset(); // Implement this to reset the candies
    startScreenText.setString("Select Level:\nPress 1, 2, or 3 to start");
}


