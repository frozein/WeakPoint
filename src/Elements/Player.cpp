#include "Player.hpp"

/*
 * FILE DESCRIPTION:
 * Includes definitions for the methods in the Player classes.
 */

Player::Player(float _x, float _y) : w(false), a(false), s(false), d(false) {
    pos = { _x, _y };
    vel = { 0, 0 };

    playerAttr = TextureAttributes(TEXTURE_PLAYER, graphics::SRC_NULL, { (int)pos.x, (int)pos.y, PLAYER_W, PLAYER_H }, 0.0, NULL, SDL_FLIP_NONE, { 255, 255, 255, 255 }, false, 1);
}

void Player::handle_input(SDL_Event e) {
    switch (e.type) {
        
    case SDL_KEYDOWN:
        switch (e.key.keysym.sym) {
            case SDLK_w: w = true; break;
            case SDLK_a: a = true; break;
            case SDLK_s: s = true; break;
            case SDLK_d: d = true; break;
            default: break;
        }
        break;

    case SDL_KEYUP:
        switch (e.key.keysym.sym) {
            case SDLK_w: w = false; break;
            case SDLK_a: a = false; break;
            case SDLK_s: s = false; break;
            case SDLK_d: d = false; break;
            default: break;
        }
        break;

    default:
        break;
    }
}

float Player::find_angle() {
    if (mousePos.x == pos.x) {
        if (mousePos.y >= pos.y)    return 0.0f;
        else                        return 180.0f;
    }

    QMvec2 delta = { mousePos.x - pos.x, mousePos.y - pos.y };
    delta = QM_vec2_normalize(delta);
    float angle = QM_rad_to_deg(acos(delta.x));
    if (delta.y > 0) angle *= -1;
    return angle;
}

void Player::update(float dt) {
    // find velocity player should be:
    vec2 findVel = { 0, 0 };
    if (w) findVel.y -= PLAYER_VEL;
    if (a) findVel.x -= PLAYER_VEL;
    if (s) findVel.y += PLAYER_VEL;
    if (d) findVel.x += PLAYER_VEL;

    if (findVel.x * findVel.x + findVel.y * findVel.y > PLAYER_VEL * PLAYER_VEL) {
        findVel.x /= sqrt(2);
        findVel.y /= sqrt(2);
    }

    // adjust for smooth acceleration:
    static const float VEL_TOLERANCE = 100;
    if (findVel.x != vel.x) {
        if (findVel.x > vel.x + VEL_TOLERANCE)          vel.x += PLAYER_ACC * dt;
        else if (findVel.x < vel.x - VEL_TOLERANCE)     vel.x -= PLAYER_ACC * dt;
        else                                            vel.x = findVel.x;
    }

    if (findVel.y != vel.y) {
        if (findVel.y > vel.y + VEL_TOLERANCE)          vel.y += PLAYER_ACC * dt;
        else if (findVel.y < vel.y - VEL_TOLERANCE)     vel.y -= PLAYER_ACC * dt;
        else                                            vel.y = findVel.y;
    }

    // apply velocity to position:
    pos.x += vel.x * dt;
    pos.y += vel.y * dt;
    playerAttr.dstRect.x = (int)pos.x;
    playerAttr.dstRect.y = (int)pos.y;

    playerAttr.angle = find_angle();
}

void Player::render() {
    graphics::render_texture(playerAttr);
}