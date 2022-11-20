#include "GameScene.hpp"

GameScene::GameScene() : gameEnd(false) {
    int tiles[MAP_W * MAP_H] = 
    {
        0, 0, 0, 0, 0, 0, 0, 0, 2, 1, 1, 1, 1, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 1, 1, 3,
        0, 0, 0, 0, 0, 0, 0, 0, 7, 5, 5, 5, 5, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 5, 5, 9,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 4, 4, 4, 4, 4, 8, 0, 0, 0, 0, 0, 0,
        0, 0, 6, 4, 4, 4, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 1, 1, 1, 1, 1, 3, 0, 0, 0, 0, 0, 0,
        0, 0, 2, 1, 1, 1, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 1, 1, 1, 1, 1, 3, 0, 0, 0, 0, 0, 0,
        0, 0, 2, 1, 1, 1, 3, 0, 6, 4, 8, 0, 0, 0, 0, 0, 0, 0, 0, 2, 1, 1, 1, 1, 1, 3, 0, 0, 0, 0, 0, 0,
        0, 0, 2, 1, 1, 1, 3, 0, 2, 1, 3, 0, 0, 0, 0, 0, 0, 0, 0, 2, 1, 1, 1, 1, 1, 3, 0, 0, 0, 0, 0, 0,
        0, 0, 2, 1, 1, 1, 3, 0, 2, 1, 3, 0, 0, 0, 0, 0, 0, 0, 0, 2, 1, 1, 1, 1, 1, 3, 0, 0, 0, 0, 0, 0,
        0, 0, 2, 1, 1, 1, 3, 0, 7, 5, 9, 0, 0, 0, 0, 0, 0, 0, 0, 7, 5, 5, 5, 5, 5, 9, 0, 0, 0, 0, 0, 0,
        0, 0, 2, 1, 1, 1, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 7, 5, 5, 5, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 4, 4, 4, 4, 4, 4, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 1, 1, 1, 1, 1, 1, 3, 0, 0, 0, 6, 4, 8, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 1, 1, 1, 1, 1, 1, 3, 0, 0, 0, 2, 1, 3, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 6, 4, 4, 4, 8, 0, 0, 0, 0, 2, 1, 1, 1, 1, 1, 1, 3, 0, 0, 0, 2, 1, 3, 0, 0, 0, 0, 6, 4, 4, 4,
        0, 2, 1, 1, 1, 3, 0, 0, 0, 0, 2, 1, 1, 1, 1, 1, 1, 3, 0, 0, 0, 2, 1, 3, 0, 0, 0, 0, 2, 1, 1, 1,
        0, 7, 5, 5, 5, 9, 0, 0, 0, 0, 7, 5, 5, 5, 5, 5, 5, 9, 0, 0, 0, 7, 5, 9, 0, 0, 0, 0, 2, 1, 1, 1,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 1, 1, 1
    };

    int props[MAP_W * MAP_H] = 
    {
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
        1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
        1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
        1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
        1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
        1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
        1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1,
        1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1,
        1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
        1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
        1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
        1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
        1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
        1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
        1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
        1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
    };

    map = new Map(MAP_W, MAP_H, (Map::TileType*)tiles, (Map::PropType*)props, WINDOW_WIDTH, WINDOW_HEIGHT);

    endscene = new EndScene();

    playerPtr = std::make_shared<Player>(500, 500, map);
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
}

GameScene::~GameScene()
{
    delete map;
    delete endscene;
}

void GameScene::handle_input(SDL_Event e) {
    if (!gameEnd)
        Scene::handle_input(e);
    else
        endscene->handle_input(e);
}

void GameScene::update(float dt)
{
    if (gameEnd) {
        endscene->update(dt);
        return;
    }

    if (playerPtr->hp == 0)
        gameEnd = true;

    score = std::to_string(playerPtr->score);
    cooldown = playerPtr->dash.cooldown > 0.0f ? std::to_string(playerPtr->dash.cooldown).substr(0, 4) : "Dash ready!";
    cooldownIndicator.dstRect.w = WINDOW_WIDTH * ((2.0f - playerPtr->dash.cooldown) / 2.0f);

    Scene::update(dt);
}

void GameScene::render()
{
    map->render();
    Scene::render();

    if (gameEnd)
        endscene->render();
}