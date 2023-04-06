/**
*   @brief      The weapon class is made to be extended into various melee and ranged weapons 
*               it is in charge of holding the weapons properties : name, damage, ammunition and frequency
*               
*   @authors    Gurshawn Lehal, Imesh Nimsitha, Gunveer Vilkhu 
*   
*/
#include "weapon.hpp"


/**
* @brief    The Weapon Constructor creates a generic weapon
*   @param name The name of the weapon
*   @param damage The damage the weapon inflicts minimum 1
*   @param maxAmmo if set to 0 or negative integer infinite ammo is assumed
*   @param frequency the frequency of the weapon's attack minimum 0
*/
Weapon::Weapon(){
    //this->name = name;
    this->damage = 100;
    this->position = (raylib::Vector2){-1000, -1000}; //non existent gun position
    this->active = false;
    this->radius = 5.0f;
    this->distance = 0;
    this->Multipier = 1;
}


/**
 * @brief deconstructor of the weapon calss
*/
Weapon::~Weapon(){

}


/**
 * @brief This makes the weapon shoot 
 * @param direction the direction the attack is headed in
 * @param Height the height of the player
 * @param playerPos the vector the player
*/
void Weapon::shoot(int direction, float Height, Vector2 playerPos){
    this->active = true;
    this->velocity.x = 1.5*sin(direction*DEG2RAD)*PLAYER_SPEED*this->Multipier;
    this->velocity.y = 1.5*cos(direction*DEG2RAD)*PLAYER_SPEED*this->Multipier;
    this->position = (Vector2){ playerPos.x + sin(direction*DEG2RAD)*(Height), playerPos.y - cos(direction*DEG2RAD)*(Height) };
}


/**
 * @brief checks if the weapon is current active 
 * @return bool if the weapon is active or not
*/
bool Weapon::isActive() {
    return this->active;
}

/**
 * @brief getPosition gets the position of the bullet currently
 * @return the vector the position
*/
raylib::Vector2 Weapon::getPosition() {
    return this->position;
}


/**
 * @brief move position, moves bullet based on velocity
*/
void Weapon::movePosition() {
    this->position.x += this->velocity.x; //add get set velocity
    this->position.y -= this->velocity.y;
    this->distance += 1;
    if (this->distance == MAX_DISTANCE) { //reset bullet if max distance is reached
        this->active=false;
        this->position = (raylib::Vector2){-1000, -1000};
        this->distance=0;
    }
}


/**
 * @brief get radius gets the radius of the bullet
 * @return float of the radius
*/
float Weapon::getRadius() {
    return this->radius;
}


/**
 * @brief set the weapon to unactive
*/
void Weapon::setUnactive() {
    this->active = false; 
    this->position = (raylib::Vector2){-1000, -1000}; //reset position
}


/**
 * @brief get the damage of the weapon
 * @return int the damage value
*/
int Weapon::getDamage() {
    return this->damage;
}


/**
 * @brief set multiplier for any type of weapon
 * @param i the multiplier value
*/
void Weapon::setMult(int i) {
    this->Multipier = i;
}


/**
 * @brief set radius for any type of weapon
 * @param i the radius value
*/
void Weapon::setRadius(float i) {
    this->radius = i;
}