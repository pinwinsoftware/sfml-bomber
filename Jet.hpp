#pragma once
#include <SFML/Graphics.hpp>

class Jet
{
public:
    void draw(sf::RenderWindow& window);

    void setTexture(sf::Texture& texture);
    void setPosition(float x, float y);
    void setScale(float x, float y);
    void update(float dt);
    sf::Vector2f getPosition() const;

private:
    sf::Sprite sprite;
    float speed = 200.f;
    int frame = 0;
    float timer = 0.f;
    float animSpeed = 0.2f;
};