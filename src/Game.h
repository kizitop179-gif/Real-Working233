#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include "Team.h"
#include "Ball.h"

class Game {
private:
    sf::RenderWindow window;
    Team teamA;   // Blue team
    Team teamB;   // Red team
    Ball ball;
    
    int scoreA = 0;
    int scoreB = 0;
    float gameTime = 0.0f;  // In seconds
    
    sf::Font font;
    sf::Text scoreText;
    sf::Text timeText;
    sf::Text instructionsText;
    
    void handleInput();
    void update(float deltaTime);
    void render();
    void checkCollisions();
    void checkGoal();
    void resetBall();
    void loadFont();
    void drawPitch();
    
public:
    Game(int width, int height);
    void run();
};

#endif
