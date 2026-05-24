#include "Tank.hpp"

void Tank::setTexture(sf::Texture& texture)
{
    sprite.setTexture(texture);

    sprite.setTextureRect(sf::IntRect(0, 0, 29, 18));
}

void Tank::setPosition(float x, float y)
{
    sprite.setPosition(x, y);
}

void Tank::setScale(float x, float y)
{
    sprite.setScale(x, y);
}

void Tank::update(float dt)
{
    sprite.move(-100.f * dt, 0.f);

    timer += dt;

    if (timer >= animSpeed)
    {
        timer = 0.f;

        frame++;
        if (frame > 3) frame = 0;

        sprite.setTextureRect(sf::IntRect(frame * 29, 0, 29, 18));
    }
}

void Tank::draw(sf::RenderWindow& window)
{
    if (alive)
        window.draw(sprite);
}

bool Tank::isAlive() const
{
    return alive;
}

void Tank::destroy()
{
    alive = false;
}

sf::Vector2f Tank::getPosition() const
{
    return sprite.getPosition();
}

sf::FloatRect Tank::getBounds() const
{
    return sprite.getGlobalBounds();
}