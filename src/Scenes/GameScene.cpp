#include "GameScene.hpp"

GameScene::GameScene() {
    playerPtr = std::make_shared<Player>(WINDOW_WIDTH / 2, WINDOW_HEIGHT - PLAYER_H / 2);
    elements.push_back(playerPtr);
}