#ifndef ENTITY_HPP
#define ENTITY_HPP
#include <SFML/Graphics.hpp>

class Entity {
public:
    virtual ~Entity() = default;
    virtual void update(float deltaTime) = 0;
    virtual void render(sf::RenderWindow& window) const = 0;
    virtual sf::Vector2f getPosition() const = 0;
    virtual bool isActive() const = 0;
    virtual void rotate(float angle) {}
    virtual void counter() {}
};

#endif // ENTITY_HPP
