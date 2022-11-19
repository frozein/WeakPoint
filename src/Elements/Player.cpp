#include "Player.hpp"

/*
 * FILE DESCRIPTION:
 * Includes definitions for the methods in the Player classes.
 */

bool Player::get_key_down(SDL_Scancode key) {
    static const Uint8* keyboardState = SDL_GetKeyboardState(nullptr);
    return keyboardState[key];
}

Player::Player(float initX, float initY) {
    canJump = true;

    playerVel = { 0.0, 0.0 };
    playerPos.x = initX;
    playerPos.y = initY;
    playerAttr = TextureAttributes(TEXTURE_PLAYER, graphics::SRC_NULL, { (int)playerPos.x, (int)playerPos.y, PLAYER_W, PLAYER_H }, 0.0, NULL, SDL_FLIP_NONE, { 255, 255, 255, 255 }, false, 1);
}

void Player::resolve_collision(int worldX, int worldY) {
    //removed this function bc its a fucking mess
}

void Player::update(float dt) {

    //--- HANDLE INPUT ---//
    // This for some reason works better here than in the handle input function lol
    // Prob bc this function is guaranteed run every frame but handle input is not

    // horizontal movement
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

    // vertical movement
    if ((get_key_down(SDL_SCANCODE_W) || get_key_down(SDL_SCANCODE_SPACE) || get_key_down(SDL_SCANCODE_UP)) && canJump) {
        playerVel.y = -JUMP_IMPULSE;
        canJump = false;
    }

    //---------------------------------------------------------------------//

    playerVel.y += GRAVITY * dt;

    if (playerPos.y >= WINDOW_HEIGHT - PLAYER_H && playerVel.y > 0) {
        canJump = true;
        playerVel.y = 0;
        playerPos.y = WINDOW_HEIGHT - PLAYER_H;
    }

    //--- check for collisions ---//

    //--- update movement ---//
    playerPos.x += playerVel.x * dt;
    playerPos.y += playerVel.y * dt;

    playerAttr.dstRect.x = (int)playerPos.x;
    playerAttr.dstRect.y = (int)playerPos.y;

}

void Player::render() {
    graphics::render_texture(playerAttr);
}