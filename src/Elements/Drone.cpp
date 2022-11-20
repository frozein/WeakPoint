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
    reloadTimer = GREENDRONE_FIRERATE;
    weakSpot = (float)(rand() % 180);
}

void Drone::fire(float speed) {
    Bullet newBullet;
    newBullet.pos = cen;

    float rad = QM_deg_to_rad(droneAttr.angle + 90.0f);
    newBullet.vel = { cosf(rad), sinf(rad) };
    newBullet.vel = QM_vec2_scale(newBullet.vel, speed);

    bullets.push_back(newBullet);
}

const int FORGIVENESS = 15;

void Drone::update(float dt) {
    SDL_Rect playerHitbox = playerPtr->playerAttr.dstRect;

    if (playerHitbox.x + PLAYER_W >= pos.x && playerHitbox.x <= pos.x + DRONE_W &&
        playerHitbox.y + PLAYER_H >= pos.y && playerHitbox.y <= pos.y + DRONE_H &&
        playerPtr->dash.dashTime > 0.0f)
    {
        int dash = (int)playerPtr->dash.angle % 180;
        int weak = (int)weakSpot % 180;
        if (abs(dash - weak) <= FORGIVENESS || abs(dash - weak) >= 180 - FORGIVENESS) { // drone has been destroyed
            active = false;
            playerPtr->score++;
            playerPtr->dash.reset_dash(true);
            return;
        }
    }

    for (int i = 0; i < bullets.size(); i++) {
        bullets.at(i).pos.x += bullets.at(i).vel.x * dt;
        bullets.at(i).pos.y += bullets.at(i).vel.y * dt;

        QMvec2 bulletHitbox = bullets.at(i).pos;

        // check if bullet is out of the window's range:
        if (bulletHitbox.x + BULLET_SIDE < 0 || bulletHitbox.x > WINDOW_WIDTH || bulletHitbox.y + BULLET_SIDE < 0 || bulletHitbox.y > WINDOW_HEIGHT)
            bullets.erase(bullets.begin() + i);

        // check if bullet contacting player:
        if (bulletHitbox.x + BULLET_SIDE >= playerHitbox.x && bulletHitbox.x <= playerHitbox.x + PLAYER_W &&
            bulletHitbox.y + BULLET_SIDE >= playerHitbox.y && bulletHitbox.y <= playerHitbox.y + PLAYER_H)
        {
            playerPtr->hp--;
            playerPtr->hurtTimer = 0.5f;
            bullets.erase(bullets.begin() + i);
        }
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

    QMvec2 rotorPos = QM_vec2_add(cen, QM_vec2_scale({cosf(QM_deg_to_rad(droneAttr.angle)), sinf(QM_deg_to_rad(droneAttr.angle))}, 75.0f));
    graphics::render_texture(TextureAttributes(TEXTURE_MULTIPURPOSE_PIXEL, graphics::SRC_NULL, { (int)(rotorPos.x), (int)(rotorPos.y), 10, 60}, (float)SDL_GetTicks(), NULL, SDL_FLIP_NONE, {70, 70, 70, 255}, true, 1));
    rotorPos = QM_vec2_add(cen, QM_vec2_scale({cosf(QM_deg_to_rad(droneAttr.angle + 180.0f)), sinf(QM_deg_to_rad(droneAttr.angle + 180.0f))}, 75.0f));
    graphics::render_texture(TextureAttributes(TEXTURE_MULTIPURPOSE_PIXEL, graphics::SRC_NULL, { (int)(rotorPos.x), (int)(rotorPos.y), 10, 60}, (float)SDL_GetTicks(), NULL, SDL_FLIP_NONE, {70, 70, 70, 255}, true, 1));

    graphics::render_texture(TextureAttributes(TEXTURE_LINE, graphics::SRC_NULL, { (int)cen.x, (int)cen.y, 195, 10 }, weakSpot, NULL, SDL_FLIP_NONE, {255, 255, 255, 255}, true, 1));
}

//----------------------------------------------------------------------//
//GREEN DRONE METHODS:

GreenDrone::GreenDrone(std::shared_ptr<Player> _playerPtr, float x, float y) : Drone(_playerPtr, x, y), reloadTimer(GREENDRONE_FIRERATE) { 
    droneAttr = TextureAttributes(TEXTURE_DRONE_GREEN, graphics::SRC_NULL, { (int)pos.x, (int)pos.y, DRONE_W, DRONE_H }, 0.0, NULL, SDL_FLIP_NONE, { 255, 255, 255, 255 }, false, 1);
}

void GreenDrone::update(float dt) {
    reloadTimer -= dt;
    if (reloadTimer <= 0.0f) {
        Drone::fire(BULLET_VEL);
        reloadTimer = GREENDRONE_FIRERATE;
    }

    Drone::update(dt);
}

//----------------------------------------------------------------------//
//PURPLE DRONE METHODS:

PurpleDrone::PurpleDrone(std::shared_ptr<Player> _playerPtr, float x, float y) : Drone(_playerPtr, x, y), timer1(2.0f), timer2(2.5f) { 
    droneAttr = TextureAttributes(TEXTURE_DRONE_PURPLE, graphics::SRC_NULL, { (int)pos.x, (int)pos.y, DRONE_W, DRONE_H }, 0.0, NULL, SDL_FLIP_NONE, { 255, 255, 255, 255 }, false, 1);
}

void PurpleDrone::update(float dt) {
    timer1 -= dt;
    timer2 -= dt;

    if (timer1 <= 0.0f) {
        Drone::fire(BULLET_VEL);
        timer1 = PURPLEDRONE_FIRERATE;
    }

    if (timer2 <= 0.0f) {
        Drone::fire(BULLET_VEL);
        timer2 = PURPLEDRONE_FIRERATE;
    }

    Drone::update(dt);
}

//----------------------------------------------------------------------//
//RED DRONE METHODS:

RedDrone::RedDrone(std::shared_ptr<Player> _playerPtr, float x, float y) : Drone(_playerPtr, x, y), reloadTimer(REDDRONE_FIRERATE) { 
    droneAttr = TextureAttributes(TEXTURE_DRONE_RED, graphics::SRC_NULL, { (int)pos.x, (int)pos.y, DRONE_W, DRONE_H }, 0.0, NULL, SDL_FLIP_NONE, { 255, 255, 255, 255 }, false, 1);
}

void RedDrone::update(float dt) {
    reloadTimer -= dt;
    if (reloadTimer <= 0.0f) {
        Drone::fire(REDBULLET_VEL);
        reloadTimer = REDDRONE_FIRERATE;
    }

    Drone::update(dt);
}