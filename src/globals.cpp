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
//FUNCTIONS:

float find_angle(QMvec2 from, QMvec2 to) {
    if (to.x == from.x) {
        if (to.y >= from.y) return 90.0f;
        else                return -90.0f;
    }

    QMvec2 delta = { to.x - from.x, to.y - from.y };
    delta = QM_vec2_normalize(delta);
    float angle = QM_rad_to_deg(acos(delta.x));
    if (delta.y < 0) angle *= -1;
    return angle;
}

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