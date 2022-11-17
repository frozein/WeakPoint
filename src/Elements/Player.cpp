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

    canJump = true;

    playerVel = { 0.0, 0.0 };
    playerPos.x = initX;
    playerPos.y = initY;
    playerAttr = TextureAttributes(TEXTURE_PLAYER, graphics::SRC_NULL, { (int)playerPos.x, (int)playerPos.y, PLAYER_W, PLAYER_H }, 0.0, NULL, SDL_FLIP_NONE, { 255, 255, 255, 255 }, false, 1);
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

    //--- detect collision ---//
    SDL_Rect collision = { 0, 0, 0, 0 };
    for (SDL_Rect platform : platforms)
        if (playerPos.x + PLAYER_W >= platform.x && playerPos.x <= platform.x + platform.w &&
            playerPos.y + PLAYER_H >= platform.y && playerPos.y <= platform.y + platform.h) {

            collision = platform;
            break;
        }

    static const int TOLERANCE = 150;

    //vertical
    playerVel.y += GRAVITY * dt;

    if (playerPos.y >= WINDOW_HEIGHT - PLAYER_H && playerVel.y > 0) {
        canJump = true;
        playerVel.y = 0;
        playerPos.y = WINDOW_HEIGHT - PLAYER_H;
    }

    if (collision.y != 0) {

        if (playerPos.y + PLAYER_H >= collision.y && playerPos.y + PLAYER_H <= collision.y + TOLERANCE && playerVel.y > 0) {
            canJump = true;
            playerVel.y = 0;
            playerPos.y = collision.y - PLAYER_H;
        }

        if (playerPos.y <= collision.y + collision.h && playerPos.y >= collision.y + collision.h - TOLERANCE &&
            playerPos.x + PLAYER_W > collision.x && playerPos.x < collision.x + collision.w) {

            playerPos.y = collision.y + collision.h + 1;
            playerVel.y = 0;
        }

    }

    // fix double jump bug
    if (collision.y == 0 && playerPos.y < WINDOW_HEIGHT - PLAYER_H) // player is in the air
        canJump = false;

    //horizontal
    if (collision.x != 0 && collision.y != playerPos.y + PLAYER_H) {

        if (playerPos.x + PLAYER_W >= collision.x && playerPos.x + PLAYER_W <= collision.x + TOLERANCE && playerVel.x > 0) {
            playerPos.x = collision.x - PLAYER_W;
            playerVel.x = 0;
        }

        if (playerPos.x <= collision.x + collision.w && playerPos.x >= collision.x + collision.w - TOLERANCE && playerVel.x < 0) {
            playerPos.x = collision.x + collision.w;
            playerVel.x = 0;
        }

    }

    //--- update horizontal movement ---//
    playerPos.x += playerVel.x * dt;
    playerPos.y += playerVel.y * dt;

    playerAttr.dstRect.x = (int)playerPos.x;
    playerAttr.dstRect.y = (int)playerPos.y;

}

void Player::render() {
    graphics::render_texture(playerAttr);
}