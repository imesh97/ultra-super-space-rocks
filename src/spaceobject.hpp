/**
 *   @brief      directive spaceobject holds a basic space class for any object that flies in space
 *               setups health position and velocity of each object
 *
 */

#ifndef SPACEOBJECT_H
#define SPACEOBJECT_H

#include <raylib-cpp.hpp>

class SpaceObject
{
protected:
    raylib::Vector2 position;
    raylib::Vector2 velocity;
    int health;

public:
    SpaceObject();
    ~SpaceObject();
    raylib::Vector2 getPosition();
    void setPosition(raylib::Vector2 newPos);
    raylib::Vector2 getVelocity();
    void setVelocity(raylib::Vector2 newVel);
    int getHealth();
    void setHealth(int modifier);
    void move();
};

#endif