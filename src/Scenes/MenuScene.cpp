#include "MenuScene.hpp"

MenuScene::MenuScene() : inGame(false) {
    logoAttr = TextureAttributes(TEXTURE_LOGO, graphics::SRC_NULL, { WINDOW_WIDTH / 2, WINDOW_HEIGHT / 5, 1475, 500 }, 0.0, NULL, SDL_FLIP_NONE, { 255, 255, 255, 255 }, true, 1);
	elements.push_back(std::make_shared<Texture>(&logoAttr));

    vignetteAttr = TextureAttributes(TEXTURE_VIGNETTE, graphics::SRC_NULL, { 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT}, 0.0, NULL, SDL_FLIP_NONE, { 255, 255, 255, 255 }, false, 1);
    elements.push_back(std::make_shared<Texture>(&vignetteAttr));

    elements.push_back(std::make_shared<MenuButton>(TextureAttributes(TEXTURE_ANIMATED_BUTTON, graphics::SRC_NULL, { 1000 , 1467, 1000, 433 }, 0.0, NULL, SDL_FLIP_NONE, { 255, 255, 255, 255 }, true, 1), &inGame, "PLAY"));
    elements.push_back(std::make_shared<MenuButton>(TextureAttributes(TEXTURE_ANIMATED_BUTTON, graphics::SRC_NULL, { WINDOW_WIDTH - 1000 , 1467, 1000, 433 }, 0.0, NULL, SDL_FLIP_NONE, { 255, 255, 255, 255 }, true, 1), &running, "QUIT"));
}

void MenuScene::update(float dt) {
    Scene::update(dt);

    logoAttr.angle = 5 * sin(time * 1.5 * M_PI);

    if (inGame)
        currentScene = std::make_unique<GameScene>();
}  