#include "GameScene.hpp"

GameScene::GameScene() {

    playerPtr = std::make_shared<Player>(500, 500);
    elements.push_back(playerPtr);

    dronePtrs.push_back(std::make_shared<Drone>(playerPtr, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2));
    elements.insert(elements.end(), dronePtrs.begin(), dronePtrs.end());

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
    Scene::update(dt);
}

void GameScene::render()
{
    map->render();
    Scene::render();
}