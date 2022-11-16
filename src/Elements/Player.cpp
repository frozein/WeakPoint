#include "Player.hpp"

/*
 * FILE DESCRIPTION:
 * Includes definitions for the methods in the Player classes.
 */

bool Player::get_key_down(SDL_Scancode key) {
    static const Uint8* keyboardState = SDL_GetKeyboardState(nullptr);
    return keyboardState[key];
}

Player::Player(float initX, float initY, std::vector< std::shared_ptr<Platform> > platformPtrs) {
    std::for_each(platformPtrs.begin(), platformPtrs.end(), [this](std::shared_ptr<Platform> platformPtr) {
        platforms.push_back(platformPtr->box);
    });

    applyGravity = false;

    playerVel = { 0.0, 0.0 };
    playerPos.x = initX;
    playerPos.y = initY;
    playerAttr = TextureAttributes(TEXTURE_PLAYER, graphics::SRC_NULL, { (int)playerPos.x, (int)playerPos.y, PLAYER_W, PLAYER_H }, 0.0, NULL, SDL_FLIP_NONE, { 255, 255, 255, 255 }, true, 1);
}

/*void Player::resolve_collision(std::shared_ptr<Platform> platformPtr) {
    static const int TOLERANCE = 100;

    if (playerPos.x + PLAYER_W / 2 < platformPtr->box.x + TOLERANCE)
        playerPos.x = platformPtr->box.x - PLAYER_W / 2;
    if (playerPos.x - PLAYER_W / 2 > platformPtr->box.x + platformPtr->box.h - TOLERANCE) {
        playerPos.x = platformPtr->box.x + platformPtr->box.h + 250;
        std::cout << "up\n";
    }
}*/

void Player::handle_input(SDL_Event e) {
    //--- HORIZONTAL MOVEMENT ---//
    if (get_key_down(SDL_SCANCODE_A) && get_key_down(SDL_SCANCODE_D))
        playerVel.x = 0;
    else if (get_key_down(SDL_SCANCODE_A)) {
        playerVel.x = -SPEED;
        playerAttr.flip = SDL_FLIP_HORIZONTAL;
    }
    else if (get_key_down(SDL_SCANCODE_D)) {
        playerVel.x = SPEED;
        playerAttr.flip = SDL_FLIP_NONE;
    }
    else
        playerVel.x = 0;

    //--- VERTICAL MOVEMENT ---//
    if ((get_key_down(SDL_SCANCODE_W) || get_key_down(SDL_SCANCODE_SPACE) || get_key_down(SDL_SCANCODE_UP)) && !applyGravity) {
        playerVel.y = -JUMP_IMPULSE;
        applyGravity = true;
    }
}

void Player::update(float dt) {
    //--- detect collision ---//
    SDL_Rect collision = { 0, 0, 0, 0 };
    for (SDL_Rect platform : platforms)
        if (playerPos.x + PLAYER_W / 2 >= platform.x && playerPos.x - PLAYER_W / 2 <= platform.x + platform.w &&
            playerPos.y + PLAYER_H / 2 >= platform.y && playerPos.y - PLAYER_H / 2 <= platform.y + platform.h) {

            collision = platform;
            break;
        }

    //horizontal
    if (collision.x != 0 && collision.y != playerPos.y + PLAYER_H / 2 &&                    // There is a collision:
       ((playerPos.x + PLAYER_W / 2 >= collision.x && playerVel.x > 0) ||                       // Collision while moving right
        (playerPos.x - PLAYER_W / 2 >= collision.x + collision.h && playerVel.x < 0))) {        // Collision while moving left

        playerVel.x = 0;
    }

    //vertical
    playerVel.y += GRAVITY * dt;

    if (playerPos.y >= WINDOW_HEIGHT - PLAYER_H / 2 && playerVel.y > 0) {
        applyGravity = false;
        playerVel.y = 0;
        playerPos.y = WINDOW_HEIGHT - PLAYER_H / 2;
    }

    if (collision.y != 0 &&
        (playerPos.y + PLAYER_H / 2 >= collision.y && playerVel.y > 0)) {

        applyGravity = false;
        playerVel.y = 0;
        playerPos.y = collision.y - PLAYER_H / 2;
    }

    //--- update vertical movement ---//
    /*if (applyGravity) {
        playerVel.y += GRAVITY * dt;
    }*/

    //--- update horizontal movement ---//
    playerPos.x += playerVel.x * dt;
    playerPos.y += playerVel.y * dt;

    playerAttr.dstRect.x = (int)playerPos.x;
    playerAttr.dstRect.y = (int)playerPos.y;

}

void Player::render() {
    graphics::render_texture(playerAttr);
}