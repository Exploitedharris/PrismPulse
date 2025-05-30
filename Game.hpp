#ifndef GAME_HPP
#define GAME_HPP
#include "Entity.hpp"
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include <random>

class Game {
private:
    sf::RenderWindow& window;
    std::vector<std::vector<float>> grid; // Lens rotation angles (degrees)
    std::vector<std::unique_ptr<Entity>> pulses; // Shadow pulses
    std::vector<std::unique_ptr<Entity>> receptors; // Crystal receptors
    std::unique_ptr<Entity> source; // Light source
    sf::Vector2i cursorPos;
    float disruption; // Disruption level (0 to 100)
    std::mt19937 rng;
    bool isAllReceptorsActive;

public:
    Game(sf::RenderWindow& win);
    void handleEvents();
    void update(float deltaTime);
    void render();
};

#endif // GAME_HPP
