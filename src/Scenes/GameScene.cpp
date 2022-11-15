#include "GameScene.hpp"

GameScene::GameScene() {
    // EXAMPLE CODE
    background = TextureAttributes(TEXTURE_MULTIPURPOSE_PIXEL, graphics::SRC_NULL, { 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT }, 0.0, NULL, SDL_FLIP_NONE, { 0, 0, 0, 255 }, false, 1.0);
    blueSquare = TextureAttributes(TEXTURE_MULTIPURPOSE_PIXEL, graphics::SRC_NULL, { 100, 100, 500, 500 }, 0.0, NULL, SDL_FLIP_NONE, { 0, 0, 255, 255 }, false, 1.0);
    text = TextureAttributes(TEXTURE_PLACEHOLDER, graphics::SRC_NULL, { 1000, 1000, 0, 0 }, 0.0, NULL, SDL_FLIP_NONE, { 255, 0, 0, 255 }, false, 3.0);

    elements.push_back(std::make_unique<Texture>(&background));
    elements.push_back(std::make_unique<Texture>(&blueSquare));
    elements.push_back(std::make_unique<ConstantText>("sumanta", &text));
}