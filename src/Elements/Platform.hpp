#pragma once
#include "Element.hpp"

/*
 * FILE DESCRIPTION:
 * Includes declarations for the Platform class.
 */

class Platform : public Element {

public:
    SDL_Rect box;

    Platform(int x, int y, int w, int h);

    void render();

};