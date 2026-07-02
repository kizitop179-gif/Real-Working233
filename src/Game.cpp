#include "Game.h"
#include <iostream>
#include <sstream>
#include <iomanip>

Game::Game(int width, int height)
    : window(sf::VideoMode(width, height), "11v11 Football Game - SFML"),
      teamA("Team A", sf::Color::Blue, 50, height),
      teamB("Team B", sf::Color::Red, width - 50, height),
      ball(width / 2.0f, height / 2.0f) {
    
    window.setFramerateLimit(60);
    loadFont();
}

void Game::loadFont() {
    if (!font.loadFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSans-Bold.ttf")) {
        #ifdef _WIN32
        font.loadFromFile("C:\\\\Windows\\\\Fonts\\\\arial.ttf");
        #endif
    }
    
    scoreText.setFont(font);
    scoreText.setCharacterSize(60);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setPosition(window.getSize().x / 2 - 80, 20);
    
    timeText.setFont(font);
    timeText.setCharacterSize(24);
    timeText.setFillColor(sf::Color::White);
    timeText.setPosition(window.getSize().x / 2 - 40, 100);
    
    instructionsText.setFont(font);
    instructionsText.setCharacterSize(12);
    instructionsText.setFillColor(sf::Color::White);
    instructionsText.setPosition(10, window.getSize().y - 80);
    instructionsText.setString("Controls: WASD/Arrows - Move | Click - Select | Space - Pass/Shoot | R - Reset");
}

void Game::handleInput() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }
        if (event.type == sf::Event::MouseButtonPressed) {
            sf::Vector2f mousePos(static_cast<float>(event.mouseButton.x),
                                 static_cast<float>(event.mouseButton.y));
            teamA.selectPlayer(mousePos);
            teamB.selectPlayer(mousePos);
        }
        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::R) {
                scoreA = 0;
                scoreB = 0;
                gameTime = 0.0f;
                resetBall();
                teamA.reset(window.getSize().x, window.getSize().y);
                teamB.reset(window.getSize().x, window.getSize().y);
            }
        }
    }
    
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) teamA.moveSelectedPlayer(0, -2);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) teamA.moveSelectedPlayer(0, 2);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) teamA.moveSelectedPlayer(-2, 0);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) teamA.moveSelectedPlayer(2, 0);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) teamA.shootWithSelected(ball);
    
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) teamB.moveSelectedPlayer(0, -2);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) teamB.moveSelectedPlayer(0, 2);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) teamB.moveSelectedPlayer(-2, 0);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) teamB.moveSelectedPlayer(2, 0);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) teamB.shootWithSelected(ball);
}

void Game::update(float deltaTime) {
    gameTime += deltaTime;
    ball.update();
    teamA.update(ball, window.getSize().x, window.getSize().y);
    teamB.update(ball, window.getSize().x, window.getSize().y);
    checkCollisions();
    checkGoal();
    
    std::stringstream ss;
    ss << scoreA << " - " << scoreB;
    scoreText.setString(ss.str());
    
    int minutes = static_cast<int>(gameTime) / 60;
    int seconds = static_cast<int>(gameTime) % 60;
    std::stringstream timeSS;
    timeSS << std::setfill('0') << std::setw(2) << minutes << ":" << std::setw(2) << seconds;
    timeText.setString(timeSS.str());
}

void Game::checkCollisions() {
    for (auto& player : teamA.getPlayers()) {
        if (ball.getBounds().intersects(player.getBounds())) {
            ball.bounce(player.getPosition());
        }
    }
    for (auto& player : teamB.getPlayers()) {
        if (ball.getBounds().intersects(player.getBounds())) {
            ball.bounce(player.getPosition());
        }
    }
    
    if (ball.getPosition().y <= 10 || ball.getPosition().y >= window.getSize().y - 10) {
        ball.reverseY();
    }
    if (ball.getPosition().x < 10) {
        ball.getPosition().x = 10;
        ball.reverseX();
    }
    if (ball.getPosition().x > window.getSize().x - 10) {
        ball.getPosition().x = window.getSize().x - 10;
        ball.reverseX();
    }
}

void Game::checkGoal() {
    float ballX = ball.getPosition().x;
    float ballY = ball.getPosition().y;
    float pitchHeight = window.getSize().y;
    float goalStartY = pitchHeight / 2 - 50;
    float goalEndY = pitchHeight / 2 + 50;
    
    if (ballX < 5 && ballY > goalStartY && ballY < goalEndY) {
        scoreB++;
        resetBall();
        teamA.reset(window.getSize().x, window.getSize().y);
        teamB.reset(window.getSize().x, window.getSize().y);
    }
    
    if (ballX > window.getSize().x - 5 && ballY > goalStartY && ballY < goalEndY) {
        scoreA++;
        resetBall();
        teamA.reset(window.getSize().x, window.getSize().y);
        teamB.reset(window.getSize().x, window.getSize().y);
    }
}

void Game::resetBall() {
    ball.reset(window.getSize().x / 2.0f, window.getSize().y / 2.0f);
}

void Game::drawPitch() {
    sf::RectangleShape centerLine(sf::Vector2f(2, window.getSize().y));
    centerLine.setPosition(window.getSize().x / 2 - 1, 0);
    centerLine.setFillColor(sf::Color::White);
    window.draw(centerLine);
    
    sf::CircleShape centerCircle(40);
    centerCircle.setPosition(window.getSize().x / 2 - 40, window.getSize().y / 2 - 40);
    centerCircle.setFillColor(sf::Color::Transparent);
    centerCircle.setOutlineThickness(2);
    centerCircle.setOutlineColor(sf::Color::White);
    window.draw(centerCircle);
    
    sf::CircleShape centerSpot(3);
    centerSpot.setPosition(window.getSize().x / 2 - 3, window.getSize().y / 2 - 3);
    centerSpot.setFillColor(sf::Color::White);
    window.draw(centerSpot);
    
    sf::RectangleShape goalAreaLeft(sf::Vector2f(40, 150));
    goalAreaLeft.setPosition(10, window.getSize().y / 2 - 75);
    goalAreaLeft.setFillColor(sf::Color::Transparent);
    goalAreaLeft.setOutlineThickness(2);
    goalAreaLeft.setOutlineColor(sf::Color::White);
    window.draw(goalAreaLeft);
    
    sf::RectangleShape goalAreaRight(sf::Vector2f(40, 150));
    goalAreaRight.setPosition(window.getSize().x - 50, window.getSize().y / 2 - 75);
    goalAreaRight.setFillColor(sf::Color::Transparent);
    goalAreaRight.setOutlineThickness(2);
    goalAreaRight.setOutlineColor(sf::Color::White);
    window.draw(goalAreaRight);
}

void Game::render() {
    window.clear(sf::Color(34, 139, 34));
    drawPitch();
    teamA.render(window);
    teamB.render(window);
    window.draw(ball.getShape());
    window.draw(scoreText);
    window.draw(timeText);
    window.draw(instructionsText);
    window.display();
}

void Game::run() {
    sf::Clock clock;
    while (window.isOpen()) {
        float deltaTime = clock.restart().asSeconds();
        handleInput();
        update(deltaTime);
        render();
    }
}
