/**
 *   @brief      soundmanager manges all sound aspects of the game
 *               the creation and load of .wav files, as well as playing the sound
 *   @authors    Gurshawn Lehal, Imesh Nimsitha, Gunveer Vilkhu 
 */

#include "soundmanager.hpp"
#include <raylib-cpp.hpp>
#include <stdlib.h>
#include <unistd.h>
#include <string>
#include <iostream>

using namespace std;


/**
 *   @brief      constructor for the sound manager
 *               creates a sound manager objects and sets up name, and boolean value of music. If the music is enabled, the music type function called
 *   @param name the name of the sound being used
 *   @param isMusic the boolean value of music flag
 */
SoundManager::SoundManager(string name, bool isMusic)
{
    this->soundName = name;
    this->isMusic = isMusic;
    if (isMusic) //if song is enabled
    {
        string path = getcwd(NULL, 0);
        this->music = LoadMusicStream((path + "/src/resources/" + name).c_str());
    }
    else //else other sound pack
    {
        string path = getcwd(NULL, 0);
        sound = LoadSound((path + "/src/resources/" + name).c_str());
    }
}

SoundManager::SoundManager()
{
}


/**
 *   @brief      deconstructor for the sound manager
 *               destroys the object and unloads based on music or sound branch
 */
SoundManager::~SoundManager()
{
    if (isMusic)
    {
        UnloadMusicStream(music);
    }
    else
    {
        UnloadSound(sound);
    }
}

/**
 *   @brief      play sound branches to the sound effect if type is not music (aka type is sound)
 */
void SoundManager::playSound()
{
    if (!isMusic)
    {
        // PlaySound(sound);
    }
}


/**
 *   @brief      play music branches to the sound effect if type is not sound
 */
void SoundManager::playMusic()
{
    if (isMusic)
    {
        PlayMusicStream(music);
    }
}

/**
 *   @brief      updates stream if not loaded properly
 *               pointer to stream changes and allows bytes to be read 
 */
void SoundManager::updateMusic()
{
    if (isMusic)
    {
        UpdateMusicStream(this->music);
    }
}

void SoundManager::updateSound(std::string name, bool isMusic)
{
    this->soundName = name;
    this->isMusic = isMusic;
    if (isMusic)
    {
        string path = getcwd(NULL, 0);
        this->music = LoadMusicStream((path + "/src/resources/" + name).c_str());
    }
    else
    {
        string path = getcwd(NULL, 0);
        sound = LoadSound((path + "/src/resources/" + name).c_str());
    }
}