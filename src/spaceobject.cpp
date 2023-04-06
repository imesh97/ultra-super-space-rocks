/**
 *   @brief      spaceobject holds a basic space class for any object that flies in space
 *               setups health position and velocity of each object
 *   @authors    Gurshawn Lehal, Imesh Nimsitha, Gunveer Vilkhu 
 */

#include "spaceobject.hpp"


/**
 *   @brief      Constructor for spaceobject
 *               setups basic positon and velocity and health of any space object
 */
SpaceObject::SpaceObject()
{
    this->position = (raylib::Vector2){0, 0};
    this->velocity = (raylib::Vector2){0, 0};
    this->health = 100;
}


/**
 *   @brief      Deconstructor for spaceobject
 *               destroys any unwanted objects
 */
SpaceObject::~SpaceObject()
{
}


/**
 *   @brief      Get position of spaceobject
 *   @return     returns a vector of the spaceobject
 */
raylib::Vector2 SpaceObject::getPosition()
{
    return this->position;
};


/**
 *   @brief      Set position of spaceobject
 *               set the new position spaceobject
 *   @param      Vector2 newPos - the vector of the new position
 */
void SpaceObject::setPosition(raylib::Vector2 newPos)
{
    this->position = newPos;
};


/**
 *   @brief      Set position of spaceobject
 *               set the new position spaceobject
 *   @param      Vector2 newPos - the vector of the new position
 *   @return     returns a vector of the velocity
 */
raylib::Vector2 SpaceObject::getVelocity()
{
    return this->velocity;
};


/**
 *   @brief      Set velocity of spaceobject
 *               set the new velocity spaceobject
 *   @param      Vector2 newVel - the vector of the new velocity
 */
void SpaceObject::setVelocity(raylib::Vector2 newVel)
{
    this->velocity = newVel;
};


/**
 *   @brief      get health of spaceobject
 *               return the health value of the space object
 *   @return     returns a int of the health
 */
int SpaceObject::getHealth()
{
    return this->health;
};


/**
 *   @brief      set health of spaceobject
 *               set a new health value of the space object
 *   @param      int modifier - value to be updated to 
 */
void SpaceObject::setHealth(int modifier)
{
    this->health = modifier;
};


/**
 *   @brief      move the spaceobject based on velocity
 *               change the space objects position based on the velocity, and update its location
 */
void SpaceObject::move()
{
    this->position.x += this->velocity.x; // new position based on velocity
    this->position.y += this->velocity.y;
};