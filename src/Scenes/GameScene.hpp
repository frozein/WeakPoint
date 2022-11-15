#pragma once
#include "Scene.hpp"
#include "simulation.hpp"
#include "Elements/Player.hpp"

class GameScene : public Scene {

private:
    std::unique_ptr<Player> player;
    sim::World* world;

public:
    GameScene();

    void update(float dt);
    void render();
};