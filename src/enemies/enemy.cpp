/**
 *   @brief      Enemy class holds the object class for the enemy
 *               has movement, health, position, and size of enemy
 *                enemy can move around like player
 *   @authors    Gurshawn Lehal, Imesh Nimsitha, Gunveer Vilkhu 
 *
 */
#include "enemy.hpp"

/**
 * @brief    Create enemy using constructor
 *           set defualt value of the enemy
 */

Enemy::Enemy()
{
    this->position = (raylib::Vector2){0, 0};
    this->velocity = (raylib::Vector2){0, 0};
    int randomRadius = GetRandomValue(20, 40);
    this->radius = randomRadius;
    this->health = 100 * (randomRadius / 30);
    this->reviveCount = 0;
}

/**
 * @brief    destroy enemy using deconstructor
 */
Enemy::~Enemy()
{
}

/**
 * @brief    Get radius of the enemy
 * @return   float of the radius of enenmy
 */
float Enemy::getRadius()
{
    return this->radius;
};

/**
 * @brief    Set radius of the enemy
 * @param   float of the radius of enenmy
 */
void Enemy::setRadius(float newRad)
{
    this->radius = newRad;
};

/**
 * @brief    Move the enemy coordinates based on the current velocity, do wall collison if needed
 */
void Enemy::move()
{
    this->position.x += this->velocity.x; // new position based on velocity (with rotation)
    this->position.y += this->velocity.y;

    if (this->position.x > SCREEN_W + this->radius)
    { // enemy is moving out of screen width -> move to other side
        this->position.x = -(this->radius);
    }
    else if (this->position.x < 0 - this->radius)
    {
        this->position.x = SCREEN_W + this->radius;
    }

    if (this->position.y > SCREEN_H + this->radius)
    { // enemy is moving out of screen height -> move to other side
        this->position.y = -(this->radius);
    }
    else if (this->position.y < 0 - this->radius)
    {
        this->position.y = SCREEN_H + this->radius;
    }
};

/**
 * @brief    get Position of the enemy
 * @return Vector2 vector of the enemy
 */
raylib::Vector2 Enemy::getPosition() {
    return this->position;
}


/**
 * @brief    set health of the enemy
 * @param health new health of the enemy
 */
void Enemy::setHealth(int health) {
    this->health = health;
}

/**
 * @brief    get health of the enemy
 * @return health of the enemy
 */
int Enemy::getHealth() {
    return this->health;
}


/**
 * @brief    add to revive count for enemy, so that they can respawn
 */
void Enemy::addReviveCount() {
    this->reviveCount += 1;
}


/**
 * @brief    get revive count for enemy
 * @return int the current count of the revive count
 */
int Enemy::getReviveCount() {
    return this->reviveCount;
}