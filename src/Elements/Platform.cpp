#include "Platform.hpp"

/*
 * FILE DESCRIPTION:
 * Includes definitions for the methods in the Platform class.
 */

Platform::Platform(int x, int y, int w, int h) {
    box = { x, y, w, h };
}

void Platform::render() {
    graphics::render_texture(TextureAttributes(TEXTURE_MULTIPURPOSE_PIXEL, graphics::SRC_NULL, box, 0.0, NULL, SDL_FLIP_NONE, { 255, 255, 255, 255 }, false, 1));
}