#include "GameScene.hpp"

GameScene::GameScene() {
    playerPtr = std::make_shared<Player>(1600, WINDOW_HEIGHT - PLAYER_H);
    elements.push_back(playerPtr);

    //temp map just for testing:
    Map::TileType tiles[] = {Map::TileType::DIRT , Map::TileType::GRASS, Map::TileType::DIRT , 
                             Map::TileType::GRASS, Map::TileType::GRASS, Map::TileType::DIRT ,
                             Map::TileType::GRASS, Map::TileType::DIRT , Map::TileType::DIRT  };
    
    Map::PropType props[] = {Map::PropType::TREE, Map::PropType::NONE, Map::PropType::TREE, 
                             Map::PropType::NONE, Map::PropType::NONE, Map::PropType::NONE,
                             Map::PropType::TREE, Map::PropType::NONE, Map::PropType::TREE };

    map = new Map(3, 3, tiles, props, 3840, 2160);
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