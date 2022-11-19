#include "globals.hpp"

/*
 * FILE DESCRIPTION:
 * Includes definitions for global functions and external variables.
 */

//------------------------------------------------------------------------------------------------//
//GLOBAL VARIABLES:

// Running state of the game
bool running = true;
// Mouse position in SDL Units
ivec2 mousePos = { 0, 0 };

//------------------------------------------------------------------------------------------------//
//VECTOR METHODS:

void vec2::normalize() {
    float len = sqrt(x * x + y * y);
    x /= len;
    y /= len;
}

vec2 vec2::operator+(const vec2& other) {
    return { this->x + other.x, this->y + other.y };
}

ivec2 ivec2::operator+(const ivec2& other) {
    return { this->x + other.x, this->y + other.y };
}