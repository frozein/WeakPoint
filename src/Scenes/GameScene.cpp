#include "GameScene.hpp"

GameScene::GameScene() {
    playerPtr = std::make_shared<Player>(500, 500);
    elements.push_back(playerPtr);

    elements.push_back(std::make_shared<RedDrone>(playerPtr, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2));

    score = "0";
    scoreText = TextureAttributes(TEXTURE_MULTIPURPOSE_PIXEL, graphics::SRC_NULL, { 100, 100, 0, 0 }, 0.0, NULL, SDL_FLIP_NONE, { 255, 255, 255, 255 }, false, 2);
    elements.push_back(std::make_shared<VariableText>(&score, &scoreText));

    cooldown = "Dash ready!";
    cooldownText = TextureAttributes(TEXTURE_MULTIPURPOSE_PIXEL, graphics::SRC_NULL, { WINDOW_WIDTH / 2, WINDOW_HEIGHT - 200, 0, 0 }, 0.0, NULL, SDL_FLIP_NONE, { 255, 255, 255, 255 }, true, 1);
    elements.push_back(std::make_shared<VariableText>(&cooldown, &cooldownText));
    cooldownIndicator = TextureAttributes(TEXTURE_MULTIPURPOSE_PIXEL, graphics::SRC_NULL, { 0, WINDOW_HEIGHT - 100, 0, 100 }, 0.0, NULL, SDL_FLIP_NONE, { 255, 255, 255, 255 }, false, 1);
    elements.push_back(std::make_shared<Texture>(&cooldownIndicator));

    //temp map just for testing:
    Map::TileType tiles[MAP_W * MAP_H];
    Map::PropType props[MAP_W * MAP_H];
    for (int i = 0; i < MAP_H; i++)
    for (int j = 0; j < MAP_W; j++) {
        tiles[i * MAP_W + j] = Map::TileType::GRASS;
        props[i * MAP_W + j] = Map::PropType::NONE;
    }

    map = new Map(MAP_W, MAP_H, tiles, props, WINDOW_WIDTH, WINDOW_HEIGHT);
}

GameScene::~GameScene()
{
    delete map;
}

void GameScene::update(float dt)
{
    /*if (playerPtr->hp == 0)
        std::cout << "game end\n";*/

    score = std::to_string(playerPtr->score);
    cooldown = playerPtr->dash.cooldown > 0.0f ? std::to_string(playerPtr->dash.cooldown).substr(0, 4) : "Dash ready!";
    cooldownIndicator.dstRect.w = WINDOW_WIDTH * (playerPtr->dash.cooldown / 2.0f);

    Scene::update(dt);
}

void GameScene::render()
{
    map->render();
    Scene::render();
}