#include "EndScene.hpp"
#include "Scenes/MenuScene.hpp"
#include "Scenes/GameScene.hpp"

EndScene::EndScene() : isRestart(false), isExit(false) {
    endText = TextureAttributes(TEXTURE_MULTIPURPOSE_PIXEL, graphics::SRC_NULL, { (int)(WINDOW_WIDTH / 2), 700, 0, 0 }, 0.0, NULL, SDL_FLIP_NONE, { 255, 255, 255, 255 }, true, 4);
    elements.push_back(std::make_shared<ConstantText>("YOU DIED", &endText));

    elements.push_back(std::make_shared<MenuButton>(TextureAttributes(TEXTURE_ANIMATED_BUTTON, graphics::SRC_NULL, { 1000 , 1467, 1000, 433 }, 0.0, NULL, SDL_FLIP_NONE, { 255, 255, 255, 255 }, true, 1), &isRestart, "RESTART"));
    elements.push_back(std::make_shared<MenuButton>(TextureAttributes(TEXTURE_ANIMATED_BUTTON, graphics::SRC_NULL, { WINDOW_WIDTH - 1000 , 1467, 1000, 433 }, 0.0, NULL, SDL_FLIP_NONE, { 255, 255, 255, 255 }, true, 1), &isExit, "EXIT"));

    vignetteAttr = TextureAttributes(TEXTURE_VIGNETTE, graphics::SRC_NULL, { 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT}, 0.0, NULL, SDL_FLIP_NONE, { 255, 255, 255, 255 }, false, 1);
    elements.push_back(std::make_shared<Texture>(&vignetteAttr));
}

void EndScene::update(float dt) {
    Scene::update(dt);

    if (isExit)
        currentScene = std::make_unique<MenuScene>();

    if (isRestart)
        currentScene = std::make_unique<GameScene>();
}  