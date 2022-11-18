#pragma once
#include "Element.hpp"
#include "../simulation.hpp"

/*
 * FILE DESCRIPTION:
 * Includes declarations for the Player class and its methods.
 */

#define WORLD_W 380
#define WORLD_H 216

//--- Player Settings ---//

#define PLAYER_W 100
#define PLAYER_H 160

#define SPEED 1000

#define JUMP_IMPULSE 1500
#define GRAVITY 5000

class Player : public Element {

private:
    sim::World* world;

    bool canJump;

    QMvec2 playerVel;

    // Returns true if the key argument is held down:
    bool get_key_down(SDL_Scancode key);

public:
    QMvec2 playerPos;

    TextureAttributes playerAttr;

    /* Create a player
     * @param initX The initial x-position of the player.
     * @param initY The initial y-position of the player.
     */
    Player(float initX, float initY, sim::World* _world);

    void resolve_collision(int worldX, int worldY);

    void update(float dt);
    void render();

};