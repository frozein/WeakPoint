#include "GameScene.hpp"

GameScene::GameScene() {
    #if DANIEL

    world = new sim::World(graphics::get_renderer(), "../../assets/art/map.png");

    #else

    world = new sim::World(graphics::get_renderer(), "art/map.png");

    #endif

    playerPtr = std::make_shared<Player>(1600, WINDOW_HEIGHT - PLAYER_H, world);
    testEnemy = new Enemy({3840.0f / 2.0f, 2160.0f / 2.0f});

    elements.push_back(playerPtr);
}

void GameScene::update(float dt)
{
    static unsigned int lastTime = SDL_GetTicks();
    const unsigned int simTime = 50;

    unsigned int curTime = SDL_GetTicks();
    if(curTime - lastTime >= simTime)
    {
        world->update();
        testEnemy->update();
        lastTime = curTime;
    }

    Scene::update(dt);
}

void GameScene::render()
{
    world->render(graphics::get_renderer(), 0, 0, 10);
    testEnemy->render();
    Scene::render();
}