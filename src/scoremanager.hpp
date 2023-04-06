/**
 *   @brief      directive score manager keeps an object to track the score of the game
 *               the score is initalized and cna be updated based on # of frames
 *   @authors    Gurshawn Lehal, Imesh Nimsitha, Gunveer Vilkhu 
 */

#ifndef SCOREMANAGER_H
#define SCOREMANAGER_H

#include <raylib-cpp.hpp>
#include <stdlib.h>
#include "constants.hpp"

class ScoreManager
{
private:
    int score;
    int highScore;
    int frames;

public:
    ScoreManager();
    ~ScoreManager();
    int getScore();
    void setScore(int modifier);
    int getHighScore();
    void setHighScore(int newHigh);
    int getFrames();
    void setFrames(int modifier);
    int load(int position);
    bool save(int position, int value);
};

#endif