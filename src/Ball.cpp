#include "Ball.h"
#include <cmath>

Ball::Ball(float x, float y) {
    shape.setRadius(6);
    shape.setPosition(x, y);
    shape.setFillColor(sf::Color::White);
    velocity = sf::Vector2f(0, 0);
}

void Ball::update() {
    shape.move(velocity);
    
    // Apply air resistance/friction
    velocity *= 0.98f;
    
    // Clamp velocity
    float speedMag = std::sqrt(velocity.x * velocity.x + velocity.y * velocity.y);
    if (speedMag > maxSpeed) {
        velocity = (velocity / speedMag) * maxSpeed;
    }
}

void Ball::bounce(sf::Vector2f playerPos) {
    // Calculate direction from player to ball
    sf::Vector2f ballPos = getPosition();
    sf::Vector2f direction = ballPos - playerPos;
    
    float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
    if (length > 0.1f) {
        direction /= length;
        velocity = direction * 6.0f;
    }
}

void Ball::reverseX() {
    velocity.x = -velocity.x * 0.8f;
}

void Ball::reverseY() {
    velocity.y = -velocity.y * 0.8f;
}

void Ball::reset(float x, float y) {
    shape.setPosition(x - shape.getRadius(), y - shape.getRadius());
    velocity = sf::Vector2f(0, 0);
}

void Ball::setVelocity(float vx, float vy) {
    velocity.x = vx;
    velocity.y = vy;
}

sf::Vector2f& Ball::getPosition() {
    static sf::Vector2f pos;
    pos = sf::Vector2f(shape.getPosition().x + shape.getRadius(),
                      shape.getPosition().y + shape.getRadius());
    return pos;
}

const sf::Vector2f& Ball::getPosition() const {
    // For const version, create a temporary
    return sf::Vector2f(shape.getPosition().x + shape.getRadius(),
                       shape.getPosition().y + shape.getRadius());
}

sf::FloatRect Ball::getBounds() const {
    return shape.getGlobalBounds();
}

sf::CircleShape Ball::getShape() const {
    return shape;
}
