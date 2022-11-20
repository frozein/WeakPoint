#include "GameScene.hpp"

GameScene::GameScene() {
    playerPtr = std::make_shared<Player>(500, 500);
    elements.push_back(playerPtr);

    score = "0";
    scoreText = TextureAttributes(TEXTURE_MULTIPURPOSE_PIXEL, graphics::SRC_NULL, { 100, 100, 0, 0 }, 0.0, NULL, SDL_FLIP_NONE, { 255, 255, 255, 255 }, false, 2);
    elements.push_back(std::make_shared<VariableText>(&score, &scoreText));

    cooldown = "Dash ready!";
    cooldownText = TextureAttributes(TEXTURE_MULTIPURPOSE_PIXEL, graphics::SRC_NULL, { WINDOW_WIDTH / 2, WINDOW_HEIGHT - 200, 0, 0 }, 0.0, NULL, SDL_FLIP_NONE, { 255, 255, 255, 255 }, true, 1);
    elements.push_back(std::make_shared<VariableText>(&cooldown, &cooldownText));
    cooldownIndicator = TextureAttributes(TEXTURE_MULTIPURPOSE_PIXEL, graphics::SRC_NULL, { 0, WINDOW_HEIGHT - 100, 0, 100 }, 0.0, NULL, SDL_FLIP_NONE, { 255, 255, 255, 255 }, false, 1);
    elements.push_back(std::make_shared<Texture>(&cooldownIndicator));

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
}

GameScene::~GameScene()
{
    delete map;
}

void GameScene::update(float dt)
{
    nextSpawn -= dt;
    if(nextSpawn <= 0.0f)
    {      
        printf("spawned\n");

        while(true)
        {
            int x = rand() % WINDOW_WIDTH;
            int y = rand() % WINDOW_HEIGHT;

            int minX, minY;
            int maxX, maxY;
            map->get_map_pos(x - DRONE_W / 2, y - DRONE_H / 2, &minX, &minY);
            map->get_map_pos(x + DRONE_W / 2, y + DRONE_H / 2, &maxX, &maxY);

            AABB temp;
            bool obstructed = false;
            for(int i = minX; i <= maxX; i++)
            for(int j = minY; j <= maxY; j++)
                obstructed = obstructed | map->aabb_at(i, j, &temp);
            
            if(!obstructed)
            {
                switch(rand() % 3)
                {
                case 0:
                    elements.push_back(std::make_shared<RedDrone>(playerPtr, x, y));
                    break;
                case 1:
                    elements.push_back(std::make_shared<GreenDrone>(playerPtr, x, y));
                    break;
                case 2:
                    elements.push_back(std::make_shared<PurpleDrone>(playerPtr, x, y));
                    break;
                }

                break;
            }
        }

        nextSpawn = (float)(rand() % 20 + 30) / (playerPtr->score + 10.0f);
    }

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