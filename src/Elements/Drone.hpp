#pragma once
#include "Element.hpp"
#include "Player.hpp"

/*
 * FILE DESCRIPTION:
 * Includes declarations for the Drone class, its subclasses, and their methods.
 */

#define BULLET_SIDE 25
#define BULLET_VEL 1500

struct Bullet {
    QMvec2 pos;
    QMvec2 vel;
};

//--- Drone Settings ---//

#define DRONE_W 110
#define DRONE_H 90

#define DRONE_FIRERATE 1.5f

class Drone : public Element {

private:
    std::shared_ptr<Player> playerPtr;
    
    QMvec2 pos;
    QMvec2 cen;
    
    float reloadTimer;
    std::vector<Bullet> bullets;
    
    TextureAttributes droneAttr;

    void fire();

public:
    Drone(std::shared_ptr<Player> _playerPtr, float x, float y);

    void update(float dt);
    void render();
};