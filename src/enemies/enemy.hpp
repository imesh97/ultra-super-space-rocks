/**
 *   @brief      Directive Enemy class holds the object class for the enemy
 *               has movement, health, position, and size of enemy
 *               enemy can move around like player
 *   @authors    Gurshawn Lehal, Imesh Nimsitha, Gunveer Vilkhu 
 *
 */

#ifndef ENEMY_H
#define ENEMY_H

#include <raylib-cpp.hpp>
#include "../spaceobject.hpp"
#include "../constants.hpp"

class Enemy : public SpaceObject
{
protected:
    float radius;
    int reviveCount;

public:
    Enemy();
    ~Enemy();
    float getRadius();
    void setRadius(float newRad);
    void move();
    raylib::Vector2 getPosition();
    void setHealth(int health);
    int getHealth();
    void addReviveCount();
    int getReviveCount();
};

#endif