#include "Game.hpp"
#include <algorithm>
#include <cmath>

class Lens : public Entity {
private:
    sf::RectangleShape shape;
    sf::Vector2f position;
    float angle; // Rotation in degrees
    bool active;

public:
    Lens(float x, float y, float a) : position(x, y), angle(a), active(true) {
        shape.setSize(sf::Vector2f(40.f, 10.f));
        shape.setFillColor(sf::Color::Cyan);
        shape.setPosition(position);
        shape.setRotation(angle);
    }

    void update(float deltaTime) override {}
    void render(sf::RenderWindow& window) const override {
        if (active) window.draw(shape);
    }
    sf::Vector2f getPosition() const override { return position; }
    bool isActive() const override { return active; }
    void rotate(float deltaAngle) override { angle += deltaAngle; shape.setRotation(angle); }
    float getAngle() const { return angle; }
};

class Pulse : public Entity {
private:
    sf::CircleShape shape;
    sf::Vector2f position;
    bool active;

public:
    Pulse(float x, float y) : position(x, y), active(true) {
        shape.setRadius(10.f);
        shape.setFillColor(sf::Color::Magenta);
        shape.setPosition(position);
    }

    void update(float deltaTime) override {}
    void render(sf::RenderWindow& window) const override {
        if (active) window.draw(shape);
    }
    sf::Vector2f getPosition() const override { return position; }
    bool isActive() const override { return active; }
    void counter() override { active = false; }
};

class Receptor : public Entity {
private:
    sf::CircleShape shape;
    sf::Vector2f position;
    bool active;

public:
    Receptor(float x, float y) : position(x, y), active(false) {
        shape.setRadius(10.f);
        shape.setFillColor(sf::Color::Yellow);
        shape.setPosition(position);
    }

    void update(float deltaTime) override {
        shape.setFillColor(active ? sf::Color::Green : sf::Color::Yellow);
    }
    void render(sf::RenderWindow& window) const override {
        window.draw(shape);
    }
    sf::Vector2f getPosition() const override { return position; }
    bool isActive() const override { return active; }
    void activate() { active = true; }
};

class Source : public Entity {
private:
    sf::CircleShape shape;
    sf::Vector2f position;
    bool active;

public:
    Source(float x, float y) : position(x, y), active(true) {
        shape.setRadius(10.f);
        shape.setFillColor(sf::Color::White);
        shape.setPosition(position);
    }

    void update(float deltaTime) override {}
    void render(sf::RenderWindow& window) const override {
        if (active) window.draw(shape);
    }
    sf::Vector2f getPosition() const override { return position; }
    bool isActive() const override { return active; }
};

Game::Game(sf::RenderWindow& win) : window(win), cursorPos(0, 0), disruption(0.f), rng(std::random_device{}()), isAllReceptorsActive(false) {
    grid.resize(5, std::vector<float>(5, 0.f));
    grid[2][1] = 45.f; // Initial lens
    grid[3][3] = 135.f; // Initial lens
    source = std::make_unique<Source>(250.f, 150.f);
    receptors.push_back(std::make_unique<Receptor>(450.f, 250.f));
    pulses.push_back(std::make_unique<Pulse>(350.f, 200.f));
}

void Game::handleEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        } else if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::R) {
                grid.assign(5, std::vector<float>(5, 0.f));
                grid[2][1] = 45.f;
                grid[3][3] = 135.f;
                pulses.clear();
                receptors.clear();
                source = std::make_unique<Source>(250.f, 150.f);
                receptors.push_back(std::make_unique<Receptor>(450.f, 250.f));
                pulses.push_back(std::make_unique<Pulse>(350.f, 200.f));
                cursorPos = {0, 0};
                disruption = 0.f;
                isAllReceptorsActive = false;
            } else if (event.key.code == sf::Keyboard::Escape) {
                window.close();
            } else if (event.key.code == sf::Keyboard::Up && cursorPos.y > 0) {
                cursorPos.y--;
            } else if (event.key.code == sf::Keyboard::Down && cursorPos.y < 4) {
                cursorPos.y++;
            } else if (event.key.code == sf::Keyboard::Left && cursorPos.x > 0) {
                cursorPos.x--;
            } else if (event.key.code == sf::Keyboard::Right && cursorPos.x < 4) {
                cursorPos.x++;
            } else if (event.key.code == sf::Keyboard::Space && grid[cursorPos.y][cursorPos.x] != 0.f) {
                grid[cursorPos.y][cursorPos.x] = fmod(grid[cursorPos.y][cursorPos.x] + 90.f, 360.f);
            } else if (event.key.code == sf::Keyboard::Enter) {
                for (auto& pulse : pulses) {
                    if (pulse->isActive() && std::abs(pulse->getPosition().x - (250.f + cursorPos.x * 50.f)) < 10.f &&
                        std::abs(pulse->getPosition().y - (150.f + cursorPos.y * 50.f)) < 10.f) {
                        pulse->counter();
                    }
                }
            }
        }
    }
}

void Game::update(float deltaTime) {
    // Update pulses
    std::uniform_int_distribution<int> dist(0, 4);
    for (auto& pulse : pulses) {
        if (pulse->isActive() && dist(rng) % 20 == 0) {
            int x = (pulse->getPosition().x - 250.f) / 50.f;
            int y = (pulse->getPosition().y - 150.f) / 50.f;
            if (x >= 0 && x < 5 && y >= 0 && y < 5 && grid[y][x] != 0.f) {
                grid[y][x] = fmod(grid[y][x] + 90.f, 360.f);
                disruption += 5.f; // Increase disruption per pulse
            }
        }
    }

    // Trace light beam
    sf::Vector2f pos = source->getPosition();
    sf::Vector2f dir(1.f, 0.f); // Rightward beam
    for (auto& receptor : receptors) {
        dynamic_cast<Receptor&>(*receptor).activate(false);
    }
    for (int i = 0; i < 10; ++i) { // Limit beam steps
        int x = (pos.x - 250.f) / 50.f;
        int y = (pos.y - 150.f) / 50.f;
        if (x >= 0 && x < 5 && y >= 0 && y < 5 && grid[y][x] != 0.f) {
            float angle = grid[y][x] * M_PI / 180.f;
            sf::Vector2f normal(cos(angle), sin(angle));
            dir = dir - 2.f * (dir.x * normal.x + dir.y * normal.y) * normal; // Reflect
        }
        pos += dir * 50.f;
        for (auto& receptor : receptors) {
            if (std::hypot(pos.x - receptor->getPosition().x, pos.y - receptor->getPosition().y) < 10.f) {
                dynamic_cast<Receptor&>(*receptor).activate(true);
            }
        }
    }

    // Update receptors
    for (auto& receptor : receptors) {
        receptor->update(deltaTime);
    }

    // Cap disruption
    if (disruption > 100.f) disruption = 100.f;

    // Check win condition
    isAllReceptorsActive = std::all_of(receptors.begin(), receptors.end(),
                                       [](const auto& r) { return r->isActive(); });
}

void Game::render() {
    window.clear(sf::Color::Black);

    // Draw grid
    for (int i = 0; i <= 5; ++i) {
        sf::Vertex line[] = {
            sf::Vertex(sf::Vector2f(250.f, 150.f + i * 50.f), sf::Color::White),
            sf::Vertex(sf::Vector2f(450.f, 150.f + i * 50.f), sf::Color::White)
        };
        window.draw(line, 2, sf::Lines);
        line[0] = sf::Vertex(sf::Vector2f(250.f + i * 50.f, 150.f), sf::Color::White);
        line[1] = sf::Vertex(sf::Vector2f(250.f + i * 50.f, 350.f), sf::Color::White);
        window.draw(line, 2, sf::Lines);
    }

    // Draw lenses
    for (int y = 0; y < 5; ++y) {
        for (int x = 0; x < 5; ++x) {
            if (grid[y][x] != 0.f) {
                Lens lens(250.f + x * 50.f, 150.f + y * 50.f, grid[y][x]);
                lens.render(window);
            }
        }
    }

    // Draw cursor
    sf::RectangleShape cursor(sf::Vector2f(50.f, 50.f));
    cursor.setFillColor(sf::Color::Transparent);
    cursor.setOutlineColor(sf::Color::Yellow);
    cursor.setOutlineThickness(2.f);
    cursor.setPosition(250.f + cursorPos.x * 50.f, 150.f + cursorPos.y * 50.f);
    window.draw(cursor);

    // Draw source, receptors, and pulses
    source->render(window);
    for (const auto& receptor : receptors) {
        receptor->render(window);
    }
    for (const auto& pulse : pulses) {
        pulse->render(window);
    }

    // Draw light beam
    sf::Vector2f pos = source->getPosition();
    sf::Vector2f dir(1.f, 0.f);
    std::vector<sf::Vertex> beam;
    beam.push_back(sf::Vertex(pos, sf::Color::White));
    for (int i = 0; i < 10; ++i) {
        int x = (pos.x - 250.f) / 50.f;
        int y = (pos.y - 150.f) / 50.f;
        if (x >= 0 && x < 5 && y >= 0 && y < 5 && grid[y][x] != 0.f) {
            float angle = grid[y][x] * M_PI / 180.f;
            sf::Vector2f normal(cos(angle), sin(angle));
            dir = dir - 2.f * (dir.x * normal.x + dir.y * normal.y) * normal;
        }
        pos += dir * 50.f;
        beam.push_back(sf::Vertex(pos, sf::Color::White));
    }
    window.draw(beam.data(), beam.size(), sf::LineStrip);

    // Draw disruption meter
    sf::RectangleShape disruptionBar(sf::Vector2f(200.f * (disruption / 100.f), 20.f));
    disruptionBar.setPosition(300.f, 50.f);
    disruptionBar.setFillColor(disruption > 80.f ? sf::Color::Red : sf::Color::Green);
    window.draw(disruptionBar);

    // Draw win/lose condition
    if (isAllReceptorsActive) {
        sf::Text winText;
        winText.setString("Receptors Activated!");
        winText.setCharacterSize(24);
        winText.setFillColor(sf::Color::Green);
        winText.setPosition(300.f, 400.f);
        window.draw(winText);
    } else if (disruption >= 100.f) {
        sf::Text loseText;
        loseText.setString("System Disrupted!");
        loseText.setCharacterSize(24);
        loseText.setFillColor(sf::Color::Red);
        loseText.setPosition(300.f, 400.f);
        window.draw(loseText);
    }

    window.display();
}
