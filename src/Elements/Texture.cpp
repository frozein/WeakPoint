#include "Texture.hpp"

/*
 * FILE DESCRIPTION:
 * Includes definitions for the methods in the Texture class.
 */

Texture::Texture(TextureAttributes* _attrPtr) {
    attrPtr = _attrPtr;
}

void Texture::render() {
    graphics::render_texture(*attrPtr);
}