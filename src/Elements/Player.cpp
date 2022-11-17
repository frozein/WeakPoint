#include "Player.hpp"

/*
 * FILE DESCRIPTION:
 * Includes definitions for the methods in the Player classes.
 */

bool Player::get_key_down(SDL_Scancode key) {
    static const Uint8* keyboardState = SDL_GetKeyboardState(nullptr);
    return keyboardState[key];
}

Player::Player(float initX, float initY, sim::World* _world) {
    world = _world;

    canJump = true;

    playerVel = { 0.0, 0.0 };
    playerPos.x = initX;
    playerPos.y = initY;
    playerAttr = TextureAttributes(TEXTURE_PLAYER, graphics::SRC_NULL, { (int)playerPos.x, (int)playerPos.y, PLAYER_W, PLAYER_H }, 0.0, NULL, SDL_FLIP_NONE, { 255, 255, 255, 255 }, false, 1);
}

const float PARTICLE_W = WINDOW_WIDTH / WORLD_W;
const float PARTICLE_H = WINDOW_HEIGHT / WORLD_H;

void Player::resolve_collision(int worldX, int worldY) {

    struct AABB {
        float x, y;
        float w, h;
    };

    AABB collision;
    collision.x = worldX * PARTICLE_W;
    collision.y = worldY * PARTICLE_H;
    collision.w = PARTICLE_W;
    collision.h = PARTICLE_H;

    //--- vertical ---//
    if (collision.y != 0) {

        if (playerPos.y + PLAYER_H >= collision.y && playerPos.y + PLAYER_H <= collision.y + collision.h && playerVel.y > 0) {
            canJump = true;
            playerVel.y = 0;
            playerPos.y = collision.y - PLAYER_H;
        }

        if (playerPos.y <= collision.y + collision.h && playerPos.y >= collision.y &&
            playerPos.x + PLAYER_W > collision.x && playerPos.x < collision.x + collision.w) {

            playerPos.y = collision.y + collision.h + 1;
            playerVel.y = 0;
        }

    }

    // fix double jump bug
    if (collision.y == 0 && playerPos.y < WINDOW_HEIGHT - PLAYER_H) // player is in the air
        canJump = false;

    //--- horizontal ---//
    if (collision.x != 0 && collision.y != playerPos.y + PLAYER_H) {

        if (playerPos.x + PLAYER_W >= collision.x && playerPos.x + PLAYER_W <= collision.x + collision.w && playerVel.x > 0) {
            playerPos.x = collision.x - PLAYER_W;
            playerVel.x = 0;
        }

        std::cout << (playerPos.x >= collision.x) << "\n";

        if (playerPos.x <= collision.x + collision.w && playerPos.x >= collision.x && playerVel.x < 0) {
            playerPos.x = collision.x + collision.w;
            playerVel.x = 0;
        }
    }
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

    int xMin = std::max((int)floor(playerPos.x / PARTICLE_W) - 1, 0);
    int xMax = std::min((int)ceil((playerPos.x + PLAYER_W) / PARTICLE_W) + 1, WORLD_W - 1);
    int yMin = std::max((int)floor(playerPos.y / PARTICLE_H) - 1, 0);
    int yMax = std::min((int)ceil((playerPos.y + PLAYER_H) / PARTICLE_H) + 1, WORLD_H - 1);

    for (int i = xMin; i <= xMax; i++)
    for (int j = yMin; j <= yMax; j++)  {
        sim::Particle* particlePtr = world->get_p(i, j);
        if (particlePtr->flag == sim::Particle::SOLID) {

            if (particlePtr->freeFall) {
                particlePtr->type = sim::Particle::AIR;
                particlePtr->flag = sim::Particle::EMPTY;
                continue;
            }

            resolve_collision(i, j);
        }
    }

    //--- update movement ---//
    playerPos.x += playerVel.x * dt;
    playerPos.y += playerVel.y * dt;

    playerAttr.dstRect.x = (int)playerPos.x;
    playerAttr.dstRect.y = (int)playerPos.y;

}

void Player::render() {
    graphics::render_texture(playerAttr);
}