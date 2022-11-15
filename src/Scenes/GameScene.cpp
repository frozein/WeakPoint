#include "GameScene.hpp"

GameScene::GameScene() {
    player = std::make_unique<Player>(WINDOW_WIDTH / 2, WINDOW_HEIGHT - PLAYER_H / 2);
    elements.push_back(std::move(player));

    #if DANIEL

    world = new sim::World(graphics::get_renderer(), "../../assets/art/map.png");

    #else

    world = new sim::World(graphics::get_renderer(), "art/map.png");

    #endif
}

void GameScene::update(float dt)
{
    static unsigned int lastTime = SDL_GetTicks();
    const unsigned int simTime = 50;

    unsigned int curTime = SDL_GetTicks();
    if(curTime - lastTime >= simTime)
    {
        world->update();
        lastTime = curTime;
    }

    Scene::update(dt);
}

void GameScene::render()
{
    world->render(graphics::get_renderer(), 0, 0, 10);

    Scene::render();
}