#pragma once
#include <SFML/Graphics.hpp>

class Gib
{
public:
    sf::Vector2f getPosition() const;
    Gib(float x, float y, sf::Color color);

    void update(float dt);
    void draw(sf::RenderWindow& window);

    bool isDead() const;

private:
    sf::RectangleShape shape;

    sf::Vector2f velocity;
    float lifetime = 1.0f;

    sf::Color color;
};