/**
 *   @brief      directive soundmanager manges all sound aspects of the game
 *               the creation and load of .wav files, as well as playing the sound
 *   @authors    Gurshawn Lehal, Imesh Nimsitha, Gunveer Vilkhu 
 */


#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H

#include <raylib-cpp.hpp>
#include <stdlib.h>
#include <unistd.h>
#include <string>

class SoundManager
{
private:
    std::string soundName;
    bool isMusic;

public:
    Music music;
    Sound sound;
    SoundManager(std::string name, bool isMusic);
    SoundManager();
    ~SoundManager();
    void playSound();
    void playMusic();
    void updateMusic();
    void updateSound(std::string name, bool isMusic);
};

#endif