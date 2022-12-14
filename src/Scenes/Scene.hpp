#pragma once
#include "IO/audio.hpp"
#include "IO/graphics.hpp"

#include "Elements/Element.hpp"
#include "Elements/Texture.hpp"
#include "Elements/Text.hpp"

/*
 * FILE DESCRIPTION:
 * Includes declarations for the Scene class and its methods.
 */

class Scene;
extern std::unique_ptr<Scene> currentScene;

class Scene {

protected:
    std::vector< std::shared_ptr<Element> > elements;
    float time;

    // Returns true if the key argument is held down:
    bool get_key_pressed(SDL_Scancode key);

public:
    Scene();

    // Use this to handle the input of all the scene's elements.
    virtual void handle_input(SDL_Event e);
    // Use this to update all of the scene's elements.
    virtual void update(float dt);
    // Use this to render all of the scene's elements.
    virtual void render();

};