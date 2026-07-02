#include "Team.h"
#include "Ball.h"

Team::Team(const std::string& teamName, sf::Color color, float startX, float pitchHeight)
    : name(teamName), teamColor(color), startX(startX), pitchHeight(pitchHeight) {
    // Formation will be initialized when needed
}

void Team::initializeFormation(float windowWidth, float windowHeight, float startX) {
    players.clear();
    
    // 11 players formation (4-3-3)
    // Goalkeeper
    if (startX < windowWidth / 2) {
        // Team A (left side)
        players.emplace_back(30, windowHeight / 2, 1, teamColor);  // GK
    } else {
        // Team B (right side)
        players.emplace_back(windowWidth - 30, windowHeight / 2, 1, teamColor);  // GK
    }
    
    // Defenders (4 players)
    float defenseY[] = {100, 200, windowHeight - 200, windowHeight - 100};
    for (int i = 0; i < 4; i++) {
        float x = (startX < windowWidth / 2) ? 150 : windowWidth - 150;
        players.emplace_back(x, defenseY[i], 2 + i, teamColor);
    }
    
    // Midfielders (3 players)
    float midfieldY[] = {150, windowHeight / 2, windowHeight - 150};
    for (int i = 0; i < 3; i++) {
        float x = (startX < windowWidth / 2) ? 400 : windowWidth - 400;
        players.emplace_back(x, midfieldY[i], 6 + i, teamColor);
    }
    
    // Forwards (3 players)
    float forwardY[] = {120, windowHeight / 2, windowHeight - 120};
    for (int i = 0; i < 3; i++) {
        float x = (startX < windowWidth / 2) ? 650 : windowWidth - 650;
        players.emplace_back(x, forwardY[i], 9 + i, teamColor);
    }
    
    selectedPlayerIndex = -1;
}

void Team::update(Ball& ball, float windowWidth, float windowHeight) {
    if (players.empty()) {
        initializeFormation(windowWidth, windowHeight, startX);
    }
    
    for (auto& player : players) {
        player.update(windowWidth, windowHeight);
    }
}

void Team::render(sf::RenderWindow& window) {
    for (auto& player : players) {
        window.draw(player.getShape());
    }
}

void Team::selectPlayer(sf::Vector2f position) {
    // Deselect previous player
    if (selectedPlayerIndex >= 0 && selectedPlayerIndex < players.size()) {
        players[selectedPlayerIndex].deselect();
    }
    
    // Find and select new player
    selectedPlayerIndex = -1;
    for (int i = 0; i < players.size(); i++) {
        if (players[i].getBounds().contains(position)) {
            players[i].select();
            selectedPlayerIndex = i;
            break;
        }
    }
}

void Team::moveSelectedPlayer(float dx, float dy) {
    if (selectedPlayerIndex >= 0 && selectedPlayerIndex < players.size()) {
        players[selectedPlayerIndex].moveTo(dx, dy);
    }
}

void Team::shootWithSelected(Ball& ball) {
    if (selectedPlayerIndex >= 0 && selectedPlayerIndex < players.size()) {
        players[selectedPlayerIndex].shoot(ball);
    }
}

void Team::reset(float windowWidth, float windowHeight) {
    initializeFormation(windowWidth, windowHeight, startX);
}

std::vector<Player>& Team::getPlayers() {
    return players;
}

const std::string& Team::getName() const {
    return name;
}
