#pragma once
#include "Scene.hpp"
#include "Scenes/EndScene.hpp"

#include "Elements/Text.hpp"
#include "Elements/Player.hpp"
#include "Elements/Drone.hpp"
#include "map.hpp"

class GameScene : public Scene {

private:
    bool gameEnd;
    EndScene* endscene;

    std::shared_ptr<Player> playerPtr;

    std::string score;
    TextureAttributes scoreText;

    std::string cooldown;
    TextureAttributes cooldownText;
    TextureAttributes cooldownIndicator;

    std::vector< std::shared_ptr<Drone> > dronePtrs;
    Map* map;

public:
    GameScene();
    ~GameScene();

    void handle_input(SDL_Event e);
    void update(float dt);
    void render();
};