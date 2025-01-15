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

#if defined(PLATFORM_WEB)
    #include <emscripten/emscripten.h>
    #include <emscripten/html5.h>
#endif

using namespace std;

Game* game = nullptr;
SoundManager* musicManager = nullptr;

void RestartGame()
{
    if (game != nullptr) {
        game->startGame();
    }
}

void MainLoop()
{
    if (game != nullptr)
    {
        // Check if game needs to restart
        if (!game->isGameOn() && (IsKeyPressed(KEY_SPACE) || IsKeyPressed(KEY_ENTER)))
        {
            RestartGame();
        }
        
        game->updateGame();
        if (musicManager != nullptr)
        {
            musicManager->updateMusic();
        }
    }
}

/**
 *   @brief      main function, allows game to be setup and run on load
 *               name, and game object are created here
 */
int main()
{
    raylib::Color textColor(LIGHTGRAY);
    raylib::Window gameWindow(SCREEN_W, SCREEN_H, "Ultra Super Space Rocks");
    SetTargetFPS(60);

    InitAudioDevice();
    musicManager = new SoundManager("music.wav", true);
    musicManager->playMusic();

    game = new Game();
    game->startGame();

    #if defined(PLATFORM_WEB)
        emscripten_set_main_loop(MainLoop, 0, 1);
    #else
        while (!gameWindow.ShouldClose())
        {
            MainLoop();
        }
    #endif

    delete game;
    delete musicManager;
    gameWindow.Close();

    return 0;
}
