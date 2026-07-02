#include "Player.h"
#include "Ball.h"
#include <cmath>

Player::Player(float x, float y, int number, sf::Color color)
    : playerNumber(number) {
    shape.setRadius(8);
    shape.setPosition(x, y);
    shape.setFillColor(color);
    shape.setOutlineThickness(2);
    shape.setOutlineColor(sf::Color::White);
    velocity = sf::Vector2f(0, 0);
}

void Player::update(float windowWidth, float windowHeight) {
    shape.move(velocity);
    velocity *= 0.95f;
    
    if (shape.getPosition().x < 0) shape.setPosition(0, shape.getPosition().y);
    if (shape.getPosition().x > windowWidth - shape.getRadius() * 2) shape.setPosition(windowWidth - shape.getRadius() * 2, shape.getPosition().y);
    if (shape.getPosition().y < 0) shape.setPosition(shape.getPosition().x, 0);
    if (shape.getPosition().y > windowHeight - shape.getRadius() * 2) shape.setPosition(shape.getPosition().x, windowHeight - shape.getRadius() * 2);
}

void Player::shoot(Ball& ball) {
    sf::Vector2f ballPos = ball.getPosition();
    sf::Vector2f playerPos = shape.getPosition();
    sf::Vector2f direction = ballPos - playerPos;
    
    float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
    if (length > 0) direction /= length;
    ball.setVelocity(direction.x * 7.0f, direction.y * 7.0f);
}

void Player::moveTo(float dx, float dy) {
    velocity.x += dx;
    velocity.y += dy;
    float maxSpeed = 5.0f;
    float speedMag = std::sqrt(velocity.x * velocity.x + velocity.y * velocity.y);
    if (speedMag > maxSpeed) velocity = (velocity / speedMag) * maxSpeed;
}

void Player::select() {
    isSelected = true;
    shape.setOutlineColor(sf::Color::Yellow);
    shape.setOutlineThickness(3);
}

void Player::deselect() {
    isSelected = false;
    shape.setOutlineColor(sf::Color::White);
    shape.setOutlineThickness(2);
}

bool Player::getSelected() const { return isSelected; }
sf::Vector2f Player::getPosition() const { return shape.getPosition(); }
sf::FloatRect Player::getBounds() const { return shape.getGlobalBounds(); }
sf::CircleShape Player::getShape() const { return shape; }
int Player::getNumber() const { return playerNumber; }
