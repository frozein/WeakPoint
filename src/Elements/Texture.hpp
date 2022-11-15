#pragma once
#include "Element.hpp"

/*
 * FILE DESCRIPTION:
 * Includes declarations for the Texture class and its functions.
 */

// Use this class to render a texture in a scene.
class Texture : public Element {

private:
    TextureAttributes* attrPtr;

public:
    Texture(TextureAttributes* _attrPtr);
    
    void render();

};