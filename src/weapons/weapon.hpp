/**
 *   @brief      Header File of the weapon class
 *   @authors    Gurshawn Lehal, Imesh Nimsitha, Gunveer Vilkhu 
 */

#ifndef WEAPON_H
#define WEAPON_H

#include <raylib-cpp.hpp>
#include "../constants.hpp"
#include <string>
#include "../soundmanager.hpp"

class Weapon
{
protected:
    raylib::Vector2 position;
    raylib::Vector2 velocity;
    std::string name;
    int damage;
    int frequency;
    bool freqCoolDown;
    bool active;
    float radius;
    int distance;
    int Multipier;

public:
    Weapon(); // set maxAmmo to 0 or negative for infinite ammo
    ~Weapon();
    void shoot(int direction, float Height, Vector2 playerPos);
    bool isActive();
    raylib::Vector2 getPosition();
    void movePosition();
    float getRadius();
    void setUnactive();
    int getDamage();
    void setMult(int i);
    void setRadius(float i);
};

#endif