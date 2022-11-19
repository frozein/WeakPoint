#include "Drone.hpp"

/*
 * FILE DESCRIPTION:
 * Includes definitions for the methods in Drone.cpp.
 */

//----------------------------------------------------------------------//
//BASE DRONE METHODS:

Drone::Drone(std::shared_ptr<Player> _playerPtr, float x, float y) {
    playerPtr = _playerPtr;
    pos = { x, y };
    cen = { pos.x + DRONE_W / 2, pos.y + DRONE_H / 2 };
    reloadTimer = DRONE_FIRERATE;
    weakSpot = (float)(rand() % 180);
    droneAttr = TextureAttributes(TEXTURE_DRONE_GREEN, graphics::SRC_NULL, { (int)pos.x, (int)pos.y, DRONE_W, DRONE_H }, 0.0, NULL, SDL_FLIP_NONE, { 255, 255, 255, 255 }, false, 1);
}

void Drone::fire() {
    Bullet newBullet;
    newBullet.pos = cen;

    float rad = QM_deg_to_rad(droneAttr.angle + 90.0f);
    newBullet.vel = { cosf(rad), sinf(rad) };
    newBullet.vel = QM_vec2_scale(newBullet.vel, BULLET_VEL);

    bullets.push_back(newBullet);
}

void Drone::update(float dt) {
    for (int i = 0; i < bullets.size(); i++) {
        bullets.at(i).pos.x += bullets.at(i).vel.x * dt;
        bullets.at(i).pos.y += bullets.at(i).vel.y * dt;

        // check if bullet is out of the window's range
        if (bullets.at(i).pos.x + BULLET_SIDE < 0 || bullets.at(i).pos.x > WINDOW_WIDTH || bullets.at(i).pos.y + BULLET_SIDE < 0 || bullets.at(i).pos.y > WINDOW_HEIGHT)
            bullets.erase(bullets.begin() + i);
    }

    // adjust angle:
    QMvec2 playerCen = { (float)playerPtr->playerAttr.dstRect.x + PLAYER_W / 2, (float)playerPtr->playerAttr.dstRect.y + PLAYER_H / 2 };
    droneAttr.angle = find_angle(cen, playerCen) - 90.0f;
}

void Drone::render() {
    std::for_each(bullets.begin(), bullets.end(), [](Bullet bullet) {
        graphics::render_texture(TextureAttributes(TEXTURE_BULLET, graphics::SRC_NULL, { (int)bullet.pos.x, (int)bullet.pos.y, BULLET_SIDE, BULLET_SIDE }, 0.0, NULL, SDL_FLIP_NONE, { 255, 255, 255, 255 }, true, 1));
    });

    graphics::render_texture(droneAttr);
    graphics::render_texture(TextureAttributes(TEXTURE_LINE, graphics::SRC_NULL, { (int)cen.x, (int)cen.y, 50, 5 }, weakSpot, NULL, SDL_FLIP_NONE, { 255, 255, 255, 255 }, true, 1));
}

//----------------------------------------------------------------------//
//GREEN DRONE METHODS:

GreenDrone::GreenDrone(std::shared_ptr<Player> _playerPtr, float x, float y) : Drone(_playerPtr, x, y), reloadTimer(DRONE_FIRERATE) { }

void GreenDrone::update(float dt) {
    reloadTimer -= dt;
    if (reloadTimer <= 0.0f) {
        Drone::fire();
        reloadTimer = DRONE_FIRERATE;
    }

    Drone::update(dt);
}