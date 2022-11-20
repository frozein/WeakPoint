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

#define DRONE_ROTVEL 40

class Drone : public Element {

private:
    std::shared_ptr<Player> playerPtr;
    
    QMvec2 cen;
    
    float reloadTimer;
    std::vector<Bullet> bullets;

    float weakSpot;
    
protected:
    QMvec2 pos;
    TextureAttributes droneAttr;

    virtual void fire(float speed);

public:
    Drone(std::shared_ptr<Player> _playerPtr, float x, float y);

    virtual void update(float dt);
    virtual void render();
};

//----------------------------------------------------------------------//
//GREEN DRONE:

#define GREENDRONE_FIRERATE 1.5f

class GreenDrone : public Drone {

private:
    float reloadTimer;

public:
    GreenDrone(std::shared_ptr<Player> _playerPtr, float x, float y);

    void update(float dt);
};

//----------------------------------------------------------------------//
//PURPLE DRONE:

#define PURPLEDRONE_FIRERATE 2.0f

class PurpleDrone : public Drone {

private:
    float timer1;
    float timer2;

public:
    PurpleDrone(std::shared_ptr<Player> _playerPtr, float x, float y);

    void update(float dt);
};

//----------------------------------------------------------------------//
//RED DRONES:

#define REDBULLET_VEL 3000
#define REDDRONE_FIRERATE 3.0f

class RedDrone : public Drone {

private:
    float reloadTimer;

public:
    RedDrone(std::shared_ptr<Player> _playerPtr, float x, float y);

    void update(float dt);
};