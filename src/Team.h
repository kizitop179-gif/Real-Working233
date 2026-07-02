#ifndef TEAM_H
#define TEAM_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "Player.h"

class Ball;

class Team {
private:
    std::string name;
    std::vector<Player> players;
    int selectedPlayerIndex = -1;
    sf::Color teamColor;
    float startX;
    float pitchHeight;
    void initializeFormation(float windowWidth, float windowHeight, float startX);
    
public:
    Team(const std::string& teamName, sf::Color color, float startX, float pitchHeight);
    void update(Ball& ball, float windowWidth, float windowHeight);
    void render(sf::RenderWindow& window);
    void selectPlayer(sf::Vector2f position);
    void moveSelectedPlayer(float dx, float dy);
    void shootWithSelected(Ball& ball);
    void reset(float windowWidth, float windowHeight);
    std::vector<Player>& getPlayers();
    const std::string& getName() const;
};

#endif
