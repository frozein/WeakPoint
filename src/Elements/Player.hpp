#pragma once
#include "Element.hpp"

/*
 * FILE DESCRIPTION:
 * Includes declarations for the Player class and its methods.
 */

//--- Player Settings ---//

#define PLAYER_W 80
#define PLAYER_H 80

#define PLAYER_VEL 750
#define PLAYER_ACC 7500 // how fast the player speeds up/slows down

class Player : public Element {

private:
    bool w, a, s, d;

    vec2 pos;
    vec2 vel;

public:
    TextureAttributes playerAttr;

    Player(float _x, float _y);

    void handle_input(SDL_Event e);

    float find_angle();
    void update(float dt);
    
    void render();
};