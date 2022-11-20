#pragma once
#include "Scene.hpp"
#include "Elements/Text.hpp"
#include "Elements/Button.hpp"

class EndScene : public Scene {

private:
    TextureAttributes endText;

    bool isRestart;
    bool isExit;

    TextureAttributes vignetteAttr;

public:
    EndScene();

    void update(float dt);
};