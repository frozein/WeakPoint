#pragma once
#include "Element.hpp"
#include "map.hpp"

/*
 * FILE DESCRIPTION:
 * Includes declarations for the Player class and any related structures and their methods.
 */

//TODO: Maybe add afterimages when dashing

//--- Dash Settings ---//

#define DASH_RESET 2.0f
#define DASH_TIME  0.15f

#define DASH_VEL 4500

struct Dash {
    float cooldown;
    float dashTime;
    float angle;
    QMvec2 vel;

    void init_dash(float _angle);
    void reset_dash(bool gotReset);
};

//--- Player Settings ---//

#define PLAYER_W 97
#define PLAYER_H 90

#define PLAYER_VEL 750
#define PLAYER_ACC 7500 // how fast the player speeds up/slows down

class Player : public Element {

private:
    Map* map;

    bool w, a, s, d;

    QMvec2 pos;
    QMvec2 vel;

public:
    unsigned int score;
    unsigned int hp;
    float hurtTimer;

    Dash dash;

    TextureAttributes playerAttr;

    Player(float _x, float _y, Map* _map);

    void resolve_collision(AABB collision, float dt, bool x);

    void handle_input(SDL_Event e);
    void update(float dt);    
    void render();
};