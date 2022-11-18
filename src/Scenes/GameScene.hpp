#pragma once
#include "Scene.hpp"
#include "simulation.hpp"
#include "Elements/Player.hpp"
#include "Elements/Platform.hpp"
#include "../enemy.hpp"

class GameScene : public Scene {

private:
    std::shared_ptr<Player> playerPtr;
    sim::World* world;

    Enemy* testEnemy;

public:
    GameScene();

    void update(float dt);
    void render();
};