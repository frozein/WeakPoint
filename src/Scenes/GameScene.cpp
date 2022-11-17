#include "GameScene.hpp"

GameScene::GameScene() {
    platformPtrs.push_back(std::make_shared<Platform>(500, WINDOW_HEIGHT - PLAYER_H - 800, 500, 400));
    platformPtrs.push_back(std::make_shared<Platform>(3000, WINDOW_HEIGHT - 400, 500, 200));
    // add platforms here

    playerPtr = std::make_shared<Player>(WINDOW_WIDTH / 2, WINDOW_HEIGHT - PLAYER_H, platformPtrs);

    elements.push_back(playerPtr);
    elements.insert(elements.end(), platformPtrs.begin(), platformPtrs.end());

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
    //world->render(graphics::get_renderer(), 0, 0, 10);

    Scene::render();
}