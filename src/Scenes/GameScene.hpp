#pragma once
#include "Scene.hpp"
#include "Elements/Player.hpp"
#include "Elements/Drone.hpp"
#include "map.hpp"

class GameScene : public Scene {

private:
    std::shared_ptr<Player> playerPtr;
    std::vector< std::shared_ptr<Drone> > dronePtrs;
    Map* map;

public:
    GameScene();
    ~GameScene();

    void update(float dt);
    void render();
};