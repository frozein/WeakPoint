#pragma once
#include "Scene.hpp"
#include "simulation.hpp"
#include "Elements/Player.hpp"
#include "Elements/Platform.hpp"

class GameScene : public Scene {

private:
    std::vector< std::shared_ptr<Platform> > platformPtrs;
    std::shared_ptr<Player> playerPtr;
    sim::World* world;

public:
    GameScene();

    void update(float dt);
    void render();
};