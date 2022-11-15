#pragma once
#include "../IO/audio.hpp"
#include "../IO/graphics.hpp"

/*
 * FILE DESCRIPTION:
 * Includes declarations for the Element class.
 */

// An element of the game is something that needs to be rendered and updated (and potentially require input to be handled).
class Element {

protected:
    std::vector< std::unique_ptr<Element> > children;
    float time;

public:
    Element();

    // Use to handle the input of an element's children.
    virtual void handle_input(SDL_Event e);
    // Use to update all of an element's children.
	virtual void update(float dt);
    // Use to render all of an element's children.
	virtual void render();

};