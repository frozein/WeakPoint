#pragma once
#include "Scene.hpp"

#include "Elements/Player.hpp"

class GameScene : public Scene {

private:
    std::unique_ptr<Player> player;

public:
    GameScene();

};