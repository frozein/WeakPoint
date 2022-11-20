#include "Player.hpp"

/*
 * FILE DESCRIPTION:
 * Includes definitions for the methods in the Player classes.
 */

//----------------------------------------------------------------------//
//DASH METHODS:

void Dash::init_dash(float _angle) {
    dashTime = DASH_TIME;
    cooldown = DASH_RESET;
    angle = _angle;
}

void Dash::reset_dash(bool gotReset) {
    if (gotReset) {
        cooldown = 0.0f;
    }
    else if (cooldown != 0.0f) {
        dashTime = 0.0f;
        cooldown = DASH_RESET;
    }
}

//----------------------------------------------------------------------//
//PLAYER METHODS:

Player::Player(float _x, float _y) : w(false), a(false), s(false), d(false), score(0), hp(3), hurtTimer(0.0f) {
    dash.dashTime = 0.0f;
    dash.cooldown = 0.0f;

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
            case SDLK_SPACE:
                if (dash.cooldown <= 0.0f) {
                    // initialize dash:
                    QMvec2 cen = { pos.x + PLAYER_W / 2, pos.y + PLAYER_H / 2 };
                    QMvec2 mouse = { (float)mousePos.x, (float)mousePos.y };
                    dash.init_dash(find_angle(cen, mouse));

                    // calculate dash velocity vector:
                    float rad = QM_deg_to_rad(dash.angle);
                    vel = { cosf(rad), sinf(rad) };
                    vel = QM_vec2_scale(vel, DASH_VEL);

                    // update player angle:
                    playerAttr.angle = find_angle(cen, mouse) - 90.0f;
                }
                break;
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

void Player::update(float dt) {
    if (hurtTimer > 0.0f) {
        hurtTimer -= dt;
        playerAttr.color = { 255, 0, 0, 255 };

        if (hurtTimer <= 0.0f)
            playerAttr.color = { 255, 255, 255, 255 };
    }

    // if dashing:
    if (dash.dashTime > 0.0f) {
        pos.x += vel.x * dt; // dash vel is calculated in handle input.
        pos.y += vel.y * dt;
        playerAttr.dstRect.x = (int)pos.x;
        playerAttr.dstRect.y = (int)pos.y; 

        // update dash:
        dash.dashTime -= dt;
        if (dash.dashTime <= 0.0f) {
            dash.reset_dash(false);
            vel = QM_vec2_normalize(vel);
            vel = QM_vec2_scale(vel, PLAYER_VEL);
        }

        return;
    }

    // find velocity player should be:
    QMvec2 findVel = { 0, 0 };
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

    QMvec2 cen = { pos.x + PLAYER_W / 2, pos.y + PLAYER_H / 2 };
    QMvec2 mouse = { (float)mousePos.x, (float)mousePos.y };
    playerAttr.angle = find_angle(cen, mouse) - 90.0f;

    // update dashing:
    if (dash.cooldown > 0.0f)
        dash.cooldown -= dt;
}

void Player::render() {
    graphics::render_texture(playerAttr);
}