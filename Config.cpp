#include "Config.hpp"

float shootTimerLimit = 0.8f;
float spawnTimerLimit = 2.f;
float introTimerLimit = 10.f;

void readConfig()
{
    std::ifstream file("config.cfg");
    std::string key;
    float value;

    while (file >> key)
    {
        size_t pos = key.find('=');
        if (pos == std::string::npos) continue;

        std::string name = key.substr(0, pos);
        value = std::stof(key.substr(pos + 1));

        if (name == "ShootTimerLimit")
            shootTimerLimit = value;

        if (name == "SpawnTimerLimit")
            spawnTimerLimit = value;

        if (name == "IntroTimerLimit")
            introTimerLimit = value;
    }
}