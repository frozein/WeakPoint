#include "Element.hpp"

/*
 * FILE DESCRIPTION:
 * Includes definitions for the methods in the Element class.
 */

Element::Element() {
    time = 0.0;
}

void Element::handle_input(SDL_Event e) {
    std::for_each(children.begin(), children.end(), [e](std::unique_ptr<Element>& child){ child->handle_input(e); });
}

void Element::update(float dt) {
    time += dt;
    std::for_each(children.begin(), children.end(), [dt](std::unique_ptr<Element>& child){ child->update(dt); });
}

void Element::render() {
    std::for_each(children.begin(), children.end(), [](std::unique_ptr<Element>& child){ child->render(); });
}