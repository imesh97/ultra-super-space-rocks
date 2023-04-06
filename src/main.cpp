/**
 *   @brief      main class, the holder of all elements in the game
 *               loads in raylib library and begins game
 *   @authors    Gurshawn Lehal, Imesh Nimsitha, Gunveer Vilkhu 
 *
 */

#include <raylib-cpp.hpp>
#include "game.hpp"
#include <unistd.h>
#include <string>
#include "soundmanager.hpp"

using namespace std;

/**
 *   @brief      main function, allows game to be setup and run on load
 *               name, and game object are created here
 */
int main()
{
    raylib::Color textColor(LIGHTGRAY);
    raylib::Window gameWindow(SCREEN_W, SCREEN_H, "Ultra Super Space Rocks"); //name of window
    SetTargetFPS(60); //fps 

    InitAudioDevice();
    SoundManager music("music.wav", true); //create sound manager

    music.playMusic(); //play music

    Game game; //game creation
    game.startGame();
    while (!gameWindow.ShouldClose()) //game loop
    {
        game.updateGame();
        music.updateMusic();
    }

    gameWindow.Close(); // end game

    return 0;
}
