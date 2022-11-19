#pragma once
#include "Scene.hpp"
#include "Elements/Player.hpp"
#include "map.hpp"

class GameScene : public Scene {

private:
    std::shared_ptr<Player> playerPtr;
    Map* map;

public:
    GameScene();
    ~GameScene();

    void update(float dt);
    void render();
};