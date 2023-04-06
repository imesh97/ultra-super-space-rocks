/**
 *   @brief      player class holds the player object
 *               creates the positon, velocity, direction, acceleration, collision, and health/radius of the object
 *   @authors    Gurshawn Lehal, Imesh Nimsitha, Gunveer Vilkhu 
 *
 */
#include "player.hpp"

/**
 *   @brief      player constructor initalizes the values of all variables to their default value
 *
 */
Player::Player()
{
    this->position = (raylib::Vector2){0, 0};
    this->velocity = (raylib::Vector2){0, 0};
    this->direction = 0.0f;
    this->accel = 0.0f;
    this->collide = (raylib::Vector3){0, 0, 0};
    this->height = 0.0f;
    this->health = 100;
    Weapon gun;
    this->gun = gun;
    this->isBigActive = false;
    // this->soundManager = SoundManager();
};


/**
 *   @brief      deallocates player values
 *
 */
Player::~Player(){};


/**
 *   @brief      captures players direction
 * @return        float of player's direction
 *
 */
float Player::getDirection()
{
    return this->direction;
};


/**
 *   @brief      sets players direction
 * @param        float of player's direction
 *
 */
void Player::setDirection(float newDir)
{
    this->direction = newDir;
};


/**
 *   @brief      captures players acceleration
 * @return        float of player's acceleration
 *
 */
float Player::getAcceleration()
{
    return this->accel;
};


/**
 *   @brief      set players acceleration
 * @param        float of player's acceleration
 *
 */
void Player::setAcceleration(float newAcc)
{
    this->accel = newAcc;
};


/**
 *   @brief      captures players collision
 * @return        vector3 of player's collision
 *
 */
raylib::Vector3 Player::getCollide()
{
    return this->collide;
};


/**
 *   @brief      set players collision
 * @param        vector3 of player's collision
 *
 */
void Player::setCollide(raylib::Vector3 newCol)
{
    this->collide = newCol;
};


/**
 *   @brief      captures players height
 * @return        float of player's height
 *
 */
float Player::getHeight()
{
    return this->height;
};


/**
 *   @brief      set players height
 * @param        float of player's height
 *
 */
void Player::setHeight(float newH)
{
    this->height = newH;
};


/**
 *   @brief      move player based on keyboard input, edit if wall collision
 *               speed up and slow down player if needed
 */
void Player::move()
{
    if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A))
    { // left key rotation
        this->direction -= 5;
    }
    if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D))
    { // right key rotation
        this->direction += 5;
    }

    if (IsKeyDown(KEY_UP) || IsKeyDown(KEY_W))
    { // up key acceleration
        if (this->accel < 1)
        {
            this->accel += 0.04f;
        }
    }
    else
    { // gradually decelerate if up key is not pressed
        if (this->accel <= 0)
        {
            this->accel = 0;
        }
        else
        {
            this->accel -= 0.02f;
        }
    }

    if (IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S))
    { // down key deceleration
        if (this->accel <= 0)
        {
            this->accel = 0;
        }
        else
        {
            this->accel -= 0.04f;
        }
    }

    if (IsKeyPressed(KEY_SPACE) && this->gun.isActive() == false) //shoot gun
    {
        // this->soundManager.updateSound("shot.wav", false);
        // this->soundManager.playSound();
        this->gun.shoot(this->direction, this->height, this->position);
    }
    else if (this->gun.isActive() == true) //move gun if active
    {
        this->gun.movePosition();
    }

    this->velocity.x = sin(this->direction * DEG2RAD) * PLAYER_SPEED; // update player velocity
    this->velocity.y = cos(this->direction * DEG2RAD) * PLAYER_SPEED;

    this->position.x += this->velocity.x * this->accel; // new player position based on velocity (with rotation) and acceleration
    this->position.y -= this->velocity.y * this->accel;

    if (this->position.x > SCREEN_W + this->height)
    { // player is moving out of screen width -> move to other side
        this->position.x = -(this->height);
    }
    else if (this->position.x < -(this->height))
    {
        this->position.x = SCREEN_W + this->height;
    }

    if (this->position.y > SCREEN_H + this->height)
    { // player is moving out of screen height -> move to other side
        this->position.y = -(this->height);
    }
    else if (this->position.y < -(this->height))
    {
        this->position.y = SCREEN_H + this->height;
    }
};


/**
 *   @brief      return the weapon class
 *   @return     Weapon, this->gun is the weapon used
 */
Weapon Player::getWeapon()
{
    return this->gun;
}


/**
 *   @brief      set the weapon to unactive
 *               when weapon is done, it is unactive, calls the weapon method
 */
void Player::setWeaponUnactive()
{
    this->gun.setUnactive();
}


/**
 *   @brief      check if big weapon is active
 *   @return     bool, True if the big weapon upgrade is currently active
 */
bool Player::checkIfBigActive() {
    return this->isBigActive;
}


/**
 *   @brief      set big weapon active
 *               Set the big weapon to active, and updates values in weapon class
 */
void Player::activateBigWeapon() {
    this->isBigActive = true;
    this->gun.setMult(2);
    this->gun.setRadius(7.0f);
}


/**
 *   @brief      reset weapon class
 *               reset from the big weapon to unactive, and updates values in weapon class
 */
void Player::deactivateBigWeapon() {
    this->isBigActive = false;
    this->gun.setMult(1);
    this->gun.setRadius(5.0f);
}