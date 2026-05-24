#include "Rocket.hpp"

void Rocket::setTexture(sf::Texture& texture)
{
    sprite.setTexture(texture);

    sprite.setTextureRect(sf::IntRect(0, 0, 14, 5));
}

void Rocket::setPosition(float x, float y)
{
    sprite.setPosition(x, y);
}

void Rocket::setScale(float x, float y)
{
    sprite.setScale(x, y);
}

void Rocket::update(float dt)
{
    sprite.move(120.f * dt, 200.f * dt);

    timer += dt;
}

void Rocket::draw(sf::RenderWindow& window)
{
    if (alive)
        window.draw(sprite);
}

bool Rocket::isAlive() const
{
    return alive;
}

void Rocket::destroy()
{
    alive = false;
}

sf::Vector2f Rocket::getPosition() const
{
    return sprite.getPosition();
}

sf::FloatRect Rocket::getBounds() const
{
    return sprite.getGlobalBounds();
}

bool Rocket::isDead() const
{
    return !alive;
}