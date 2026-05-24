#include "Gibs.hpp"
#include <cstdlib>

Gib::Gib(float x, float y, sf::Color c)
{
    shape.setSize(sf::Vector2f(2.f, 2.f)); // gib size
    shape.setPosition(x, y);

    color = c;
    shape.setFillColor(color);

    velocity.x = (std::rand() % 200 - 100) * 0.9f; // random horizontal burst for explosion debris
    velocity.y = -(std::rand() % 200 + 100); // upward explosion force so debris shoots into air first

    lifetime = 1.f;
}

void Gib::update(float dt)
{
    velocity.y += 250.f * dt; // gravity

    shape.move(velocity * dt);

    lifetime -= dt;
}

bool Gib::isDead() const
{
    return lifetime <= 0.f;
}

void Gib::draw(sf::RenderWindow& window)
{
    window.draw(shape);
}

sf::Vector2f Gib::getPosition() const
{
    return shape.getPosition();
}