#include <SFML/Graphics.hpp>
#include "Tank.hpp"
#include "Jet.hpp"
#include "Rocket.hpp"
#include "Gibs.hpp"
#include "Config.hpp"
#include <windows.h>

enum GameState
{
    Intro,
    Playing
};

GameState gameState = Intro;

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
    sf::Clock clock;
    sf::RenderWindow window(sf::VideoMode(640, 480), "Bomber", sf::Style::Fullscreen);
    window.setVerticalSyncEnabled(true);

    std::vector<Rocket> rockets;
    std::vector<Tank> enemies;
    std::vector<Gib> gibs;

    sf::Font font;

    font.loadFromFile("graphics/437.ttf");

    sf::Text scoreText;

    scoreText.setFont(font);
    scoreText.setCharacterSize(32);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setPosition(window.getSize().x / 2 - 24 * 3, 5.f);

    // textures
    sf::Texture groundTexture;
    groundTexture.loadFromFile("graphics/1.png");

    sf::Texture tankTexture;
    tankTexture.loadFromFile("graphics/tank.png");

    sf::Texture jetTexture;
    jetTexture.loadFromFile("graphics/jet.png");

    sf::Texture rocketTexture;
    rocketTexture.loadFromFile("graphics/rocket.png");

    // textures used for gib particles
    sf::Image tankImage;
    tankImage.loadFromFile("graphics/tank.png");

    sf::Image rocketImage;
    rocketImage.loadFromFile("graphics/rocket.png");

    const int tileSize = 32;
    int layers = 2;
    float spawnTimer = 0.f;
    float shootTimer = 0.f;
    float introTimer = 0.f;
    int Score = 0;

    Tank t;

    t.setTexture(tankTexture);
    t.setPosition(window.getSize().x, 380);
    t.setScale(2.f, 2.f);

    enemies.push_back(t);

    Jet player;
    player.setTexture(jetTexture);
    player.setPosition(0, window.getSize().y / 10);
    player.setScale(2.0f, 2.0f);

    groundTexture.setSmooth(false);
    tankTexture.setSmooth(false);
    jetTexture.setSmooth(false);
    rocketTexture.setSmooth(false);

    sf::Sprite grassTile(groundTexture);

    grassTile.setScale(2.0f, 2.0f);

    sf::Text titleText;
    sf::Text authorText;
    sf::Text copyrightText;

    titleText.setFont(font);
    authorText.setFont(font);
    copyrightText.setFont(font);

    titleText.setString("*** BOMBER ***");
    titleText.setCharacterSize(32);
    authorText.setString("By Pinwin");
    authorText.setCharacterSize(32);
    copyrightText.setString("(C) 2026 Pinwin Software");
    copyrightText.setCharacterSize(32);

    titleText.setFillColor(sf::Color::White);
    authorText.setFillColor(sf::Color::White);
    copyrightText.setFillColor(sf::Color::White);

    titleText.setPosition(
        window.getSize().x / 2 - 125,
        window.getSize().y / 2 - 68
    );

    authorText.setPosition(
        window.getSize().x / 2 - 79,
        window.getSize().y / 2 - 20
    );

    copyrightText.setPosition(
        window.getSize().x / 2 - 216,
        window.getSize().y / 2 + 28
    );

    while (window.isOpen())
    {
        sf::Event event;

        float dt = clock.restart().asSeconds();
        spawnTimer += dt;
        shootTimer += dt;
        introTimer += dt;

        if (gameState == Intro)
        {
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed) {
                    window.close();
                }
            }

            if (introTimer >= introTimerLimit)
            {
                gameState = Playing;
            }

            window.clear(sf::Color::Black);

            window.draw(titleText);
            window.draw(authorText);
            window.draw(copyrightText);

            window.display();

            readConfig();
        }

        else if (gameState == Playing)
        {
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    window.close();

                if (event.type == sf::Event::KeyPressed)
                {

                    if (event.key.code == sf::Keyboard::Space)
                    {
                        if (shootTimer >= shootTimerLimit)
                        {
                            shootTimer = 0.f;

                            Rocket r;
                            r.setTexture(rocketTexture);
                            r.setScale(2.0f, 2.0f);

                            r.setPosition(player.getPosition().x + 55, window.getSize().y / 10 + 24);

                            rockets.push_back(r);
                        }
                    }

                    if (event.key.code == sf::Keyboard::Escape)
                    {
                        window.close();
                    }
                }
            }

            enemies.erase(
                std::remove_if(enemies.begin(), enemies.end(),
                    [&](Tank& e)
                    {
                        return
                            !e.isAlive() ||
                            e.getPosition().x <= -29 * 2;
                    }),
                enemies.end()
            );

            // if rocket reaches ground
            for (auto& r : rockets)
            {
                if (r.getPosition().y >= window.getSize().y - 5 * 2 - tileSize * 2)
                {
                    for (int y = 0; y < 5; y++)
                    {
                        for (int x = 0; x < 14; x++)
                        {
                            sf::Color color = rocketImage.getPixel(x, y);

                            if (color.a == 0)
                                continue;

                            gibs.emplace_back(
                                r.getPosition().x + x,
                                r.getPosition().y + y - 5,
                                color
                            );
                        }
                    }

                    r.destroy();
                }
            }

            rockets.erase(
                std::remove_if(rockets.begin(), rockets.end(),
                    [](Rocket& r)
                    {
                        return r.isDead();
                    }),
                rockets.end()
            );

            gibs.erase(
                std::remove_if(gibs.begin(), gibs.end(),
                    [&](Gib& g)
                    {
                        return g.getPosition().y >= window.getSize().y - 32 * 2;
                    }),
                gibs.end()
            );

            if (player.getPosition().x >= window.getSize().x)
            {
                player.setPosition(-55 * 2, window.getSize().y / 10);
            }

            if (spawnTimer >= spawnTimerLimit)
            {
                spawnTimer = 0.f;

                Tank t;

                t.setTexture(tankTexture);
                t.setPosition(window.getSize().x, 380);
                t.setScale(2.f, 2.f);

                enemies.push_back(t);
            }

            window.clear(sf::Color(22, 22, 22));

            int tileCount = window.getSize().x / tileSize;
            int groundY = window.getSize().y - tileSize;

            // draw ground
            for (int y = 0; y < layers; y++)
            {
                for (int x = 0; x < tileCount; x++)
                {
                    grassTile.setPosition(
                        x * tileSize,
                        groundY - (y * tileSize)
                    );

                    window.draw(grassTile);
                }
            }

            for (auto& e : enemies)
            {
                e.update(dt);
                e.draw(window);
            }

            // update + draw rockets
            for (auto& r : rockets)
            {
                r.update(dt);
                r.draw(window);
            }

            // update draw + gibs
            for (auto& g : gibs) {
                g.update(dt);
                g.draw(window);
            }

            // if rocket reaches tank
            for (auto& r : rockets)
            {
                for (auto& e : enemies)
                {
                    if (r.getBounds().intersects(e.getBounds()))
                    {
                        e.destroy();
                        Score += 100;
                        r.destroy();

                        for (int y = 0; y < 18; y++)
                        {
                            for (int x = 0; x < 29; x++)
                            {
                                sf::Color color = tankImage.getPixel(x, y);

                                if (color.a == 0)
                                    continue;

                                gibs.emplace_back(
                                    e.getPosition().x + x + 18,
                                    e.getPosition().y + y + 18,
                                    color
                                );
                            }
                        }
                    }
                }
            }

            player.update(dt);
            player.draw(window);

            scoreText.setString("Score: " + std::to_string(Score));
            window.draw(scoreText);

            window.display();
        }
    }

    return 0;
}