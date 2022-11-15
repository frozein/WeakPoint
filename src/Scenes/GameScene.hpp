#pragma once
#include "Scene.hpp"

#include "Elements/Player.hpp"

class GameScene : public Scene {

private:
    std::shared_ptr<Player> playerPtr;

public:
    GameScene();

};