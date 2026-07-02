#ifndef BALL_H
#define BALL_H

#include <SFML/Graphics.hpp>

class Ball {
private:
    sf::CircleShape shape;
    sf::Vector2f velocity;
    float maxSpeed = 10.0f;
    
public:
    Ball(float x, float y);
    
    void update();
    void bounce(sf::Vector2f playerPos);
    void reverseX();
    void reverseY();
    void reset(float x, float y);
    void setVelocity(float vx, float vy);
    
    sf::Vector2f& getPosition();
    const sf::Vector2f& getPosition() const;
    sf::FloatRect getBounds() const;
    sf::CircleShape getShape() const;
};

#endif
