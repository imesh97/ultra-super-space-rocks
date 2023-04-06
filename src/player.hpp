/**
 *   @brief      directive player creates the player object and allows the setup of movement and other aspects
 *               the score is initalized and cna be updated based on # of frames
 *   @authors    Gurshawn Lehal, Imesh Nimsitha, Gunveer Vilkhu 
 */

#ifndef PLAYER_H
#define PLAYER_H

#include <raylib-cpp.hpp>
#include "spaceobject.hpp"
#include "constants.hpp"
#include "weapons/weapon.hpp"
#include "soundmanager.hpp"

class Player : public SpaceObject
{
private:
    float direction;
    float accel;
    raylib::Vector3 collide;
    float height;
    int health;
    Weapon gun;
    bool isBigActive;

public:
    Player();
    ~Player();
    float getDirection();
    void setDirection(float newDir);
    float getAcceleration();
    void setAcceleration(float newAcc);
    raylib::Vector3 getCollide();
    void setCollide(raylib::Vector3 newCol);
    float getHeight();
    void setHeight(float newH);
    void move();
    Weapon getWeapon();
    void setWeaponUnactive();
    bool checkIfBigActive();
    void activateBigWeapon();
    void deactivateBigWeapon();
};

#endif