#include "Player.hpp"

/*
 * FILE DESCRIPTION:
 * Includes definitions for the methods in the Player classes.
 */

bool Player::get_key_pressed(SDL_Scancode key) {
    static const Uint8* keyboardState = SDL_GetKeyboardState(nullptr);
    return keyboardState[key];
}

Player::Player(float initX, float initY) {
    playerVel = { 0.0, 0.0 };
    playerPos.x = initX;
    playerPos.y = initY;
    playerAttr = TextureAttributes(TEXTURE_PLAYER, graphics::SRC_NULL, { (int)playerPos.x, (int)playerPos.y, PLAYER_W, PLAYER_H }, 0.0, NULL, SDL_FLIP_NONE, { 255, 255, 255, 255 }, true, 1);
}

void Player::handle_input(SDL_Event e) {
    //--- VERTICAL MOVEMENT ---//
    if (get_key_pressed(SDL_SCANCODE_A)) {
        playerVel.x = -SPEED;
        playerAttr.flip = SDL_FLIP_HORIZONTAL;
    }
    else if (get_key_pressed(SDL_SCANCODE_D)) {
        playerVel.x = SPEED;
        playerAttr.flip = SDL_FLIP_NONE;
    }
    else
        playerVel.x = 0;
}

void Player::update(float dt) {

    playerPos.x += playerVel.x * dt;
    playerPos.y += playerVel.y * dt;

    playerAttr.dstRect.x = (int)playerPos.x;
    playerAttr.dstRect.y = (int)playerPos.y;

}

void Player::render() {
    graphics::render_texture(playerAttr);
}