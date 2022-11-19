#pragma once
#include <iostream>
#include <string>
#include <chrono>
#include <memory>
#include <exception>

//--- Standard Template Libraries ---//
#include <array>
#include <vector>
#include <algorithm>

//--- QuickMath ---//
#include "quickmath.h"

/*
 * FILE DESCRIPTION:
 * Includes globally relevant information.
 */

#define DANIEL 0

extern bool running;
struct ivec2;
extern ivec2 mousePos;

//------------------------------------------------------------------------------------------------//
//GLOBAL DATA TYPES:

// A 2D point of floats.
struct vec2 {
    float x;
    float y;

    void normalize();

    /* Add functionality for two float vectors.
     * @param other Other float vector to add.
     * @return Sum of the current vector and the argument vector.
     */
    vec2 operator+(const vec2& other);
};

// A 2D point of integers.
struct ivec2 {
    int x;
    int y;

    /* Add functionality for two integer vectors.
     * @param other Other integer vector to add.
     * @return Sum of the current vector and the argument vector.
     */
    ivec2 operator+(const ivec2& other);
};