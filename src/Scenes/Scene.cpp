#include "Scene.hpp"

/*
 * FILE DESCRIPTION:
 * Includes definitions for the methods of the Scene class.
 */

// The current scene of the game.
std::unique_ptr<Scene> currentScene;

bool Scene::get_key_pressed(SDL_Scancode key) {
    static const Uint8* keyboardState = SDL_GetKeyboardState(nullptr);
    return keyboardState[key];
}

Scene::Scene() {
    time = 0.0;
}

void Scene::handle_input(SDL_Event e) {
    std::for_each(elements.begin(), elements.end(), [e](std::shared_ptr<Element> element){ element->handle_input(e); });
}

void Scene::update(float dt) {
    time += dt;

    for (int i = 0; i < elements.size(); i++) {
        elements.at(i)->update(dt);

        if (!elements.at(i)->active)
            elements.erase(elements.begin() + i);
    }
}

void Scene::render() {
    std::for_each(elements.begin(), elements.end(), [](std::shared_ptr<Element> element){ element->render(); });
}