#pragma once
#include "Element.hpp"
#include "Player.hpp"

/*
 * FILE DESCRIPTION:
 * Includes declarations for the Drone class, its subclasses, and their methods.
 */

//----------------------------------------------------------------------//
//BULLET CLASS:

#define BULLET_SIDE 25
#define BULLET_VEL 1500

struct Bullet {
    QMvec2 pos;
    QMvec2 vel;
};

//----------------------------------------------------------------------//
//BASE DRONE CLASS:

#define DRONE_W 110
#define DRONE_H 90

class Drone : public Element {

private:
    std::shared_ptr<Player> playerPtr;
    
    QMvec2 pos;
    QMvec2 cen;
    
    float reloadTimer;
    std::vector<Bullet> bullets;

    float weakSpot;
    
    TextureAttributes droneAttr;

protected:
    void fire();

public:
    Drone(std::shared_ptr<Player> _playerPtr, float x, float y);

    virtual void update(float dt);
    virtual void render();
};

//----------------------------------------------------------------------//
//GREEN DRONE:

#define DRONE_FIRERATE 1.5f

class GreenDrone : public Drone {

private:
    float reloadTimer;

public:
    GreenDrone(std::shared_ptr<Player> _playerPtr, float x, float y);

    void update(float dt);
};