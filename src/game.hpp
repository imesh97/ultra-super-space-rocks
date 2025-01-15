/**
 *   @brief      directive game class holds the game where the game loop occurs
 *               setup game mechanics such has inital value of the player and health, among other variables
 *   @authors    Gurshawn Lehal, Imesh Nimsitha, Gunveer Vilkhu 
 *
 */

#ifndef GAME_H
#define GAME_H

#include <raylib-cpp.hpp>
#include "math.h"
#include "scoremanager.hpp"
#include "player.hpp"
#include "enemies/enemy.hpp"
#include "constants.hpp"
#include <cstring>
#include "soundmanager.hpp"

class Game
{
private:
    ScoreManager scoreManager;
    Player player;
    Enemy enemies[MAX_ENEMIES];
    bool gameOn;
    bool gamePause;
    bool activePowerup;
    float rotation;
    float upgradeX;
    float upgradeY;
    int bigWeaponCount;

public:
    Game();
    ~Game();
    void startGame();
    void updateGame();
    void drawGame();
    void pauseGame();
    bool isGameOn();
};

#endif