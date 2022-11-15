#pragma once
#include "Element.hpp"

/*
 * FILE DESCRIPTION:
 * Includes declarations for the Player class and its methods.
 */

#define PLAYER_W 200
#define PLAYER_H 320
#define SPEED 1500

class Player : public Element {

private:
    QMvec2 playerPos;
    QMvec2 playerVel;

    // Returns true if the key argument is held down:
    bool get_key_pressed(SDL_Scancode key);

public:
    TextureAttributes playerAttr;

    /* Create a player
     * @param initX The initial x-position of the player.
     * @param initY The initial y-position of the player.
     */
    Player(float initX, float initY);

    void handle_input(SDL_Event e);
    void update(float dt);
    void render();

};