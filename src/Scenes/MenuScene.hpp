#pragma once
#include "Scene.hpp"
#include "GameScene.hpp"
#include "Elements/Texture.hpp"
#include "Elements/Button.hpp"

class MenuScene : public Scene {

private:
    bool inGame;
    TextureAttributes logoAttr;

public:
    MenuScene();

    void update(float dt);
};