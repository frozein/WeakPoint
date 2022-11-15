#include "GameScene.hpp"

GameScene::GameScene() {
    player = std::make_unique<Player>(WINDOW_WIDTH / 2, WINDOW_HEIGHT - PLAYER_H / 2);
    elements.push_back(std::move(player));
}