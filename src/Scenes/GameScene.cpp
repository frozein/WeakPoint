#include "GameScene.hpp"

GameScene::GameScene() {
    playerPtr = std::make_shared<Player>(1600, WINDOW_HEIGHT - PLAYER_H);
    elements.push_back(playerPtr);
}

void GameScene::update(float dt)
{
    Scene::update(dt);
}

void GameScene::render()
{
    Scene::render();
}