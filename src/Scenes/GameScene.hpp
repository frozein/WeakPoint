#pragma once
#include "Scene.hpp"
#include "Elements/Text.hpp"
#include "Elements/Player.hpp"
#include "Elements/Drone.hpp"
#include "map.hpp"

class GameScene : public Scene {

private:
    std::shared_ptr<Player> playerPtr;

    std::string score;
    TextureAttributes scoreText;

    std::string cooldown;
    TextureAttributes cooldownText;
    TextureAttributes cooldownIndicator;

    std::vector< std::shared_ptr<Drone> > dronePtrs;
    Map* map;

    float nextSpawn = 3.0f;

public:
    GameScene();
    ~GameScene();

    void update(float dt);
    void render();
};