#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>

class Ball;  // Forward declaration

class Player {
private:
    sf::CircleShape shape;
    sf::Vector2f velocity;
    float speed = 3.0f;
    int playerNumber;
    bool isSelected = false;
    
public:
    Player(float x, float y, int number, sf::Color color);
    
    void update(float windowWidth, float windowHeight);
    void shoot(Ball& ball);
    void moveTo(float dx, float dy);
    
    void select();
    void deselect();
    bool getSelected() const;
    
    sf::Vector2f getPosition() const;
    sf::FloatRect getBounds() const;
    sf::CircleShape getShape() const;
    
    int getNumber() const;
};

#endif
