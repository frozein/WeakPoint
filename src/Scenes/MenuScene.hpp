#pragma once
#include "Scene.hpp"
#include "map.hpp"
#include "Elements/Texture.hpp"
#include "Elements/Button.hpp"

class MenuScene : public Scene {

private:
    bool inGame;
    TextureAttributes logoAttr;
    TextureAttributes vignetteAttr;
    Map* map;

public:
    MenuScene();
    ~MenuScene();

    void update(float dt);
    void render();
};