#include "Jet.hpp"

void Jet::setTexture(sf::Texture& texture)
{
    sprite.setTexture(texture);

    sprite.setTextureRect(sf::IntRect(0, 0, 55, 18));
}

void Jet::setPosition(float x, float y)
{
    sprite.setPosition(x, y);
}

void Jet::setScale(float x, float y)
{
    sprite.setScale(x, y);
}

int frames[] = { 0, 1, 2, 3, 2, 1 };
int frameIndex = 0;

void Jet::update(float dt)
{
    sprite.move(120.f * dt, 0.f);

    timer += dt;

    int frames[] = { 0, 1, 2, 3, 2, 1 };
    int frameCount = 6;

    if (timer >= animSpeed)
    {
        timer = 0.f;

        frameIndex++;

        if (frameIndex >= frameCount)
            frameIndex = 0;

        int frame = frames[frameIndex];

        sprite.setTextureRect(sf::IntRect(frame * 55, 0, 55, 18));
    }
}

void Jet::draw(sf::RenderWindow& window)
{
    window.draw(sprite);
}

sf::Vector2f Jet::getPosition() const
{
    return sprite.getPosition();
}