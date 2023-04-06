/**
 *   @brief      game class holds the game where the game loop occurs
 *               setup game mechanics such has inital value of the player and health, among other variables
 *   @authors    Gurshawn Lehal, Imesh Nimsitha, Gunveer Vilkhu 
 */
#include "game.hpp"


/**
 *   @brief      Game constructor, constructs game object
 *
 */
Game::Game()
{
    this->gameOn = false;
    this->gamePause = false;
    this->activePowerup = false;
    this->rotation = 0.0f;
    this->bigWeaponCount = 0;
};


/**
 *   @brief      Game deconstructor, deconstructs game object
 *
 */
Game::~Game(){};


/**
 *   @brief      Start game method, allows game processes to load in and begin with their inital values, call enemies as well
 *               set player, enemy default positions
 *
 */
void Game::startGame()
{
    float initHeight = (PLAYER_SIZE / 2) / tanf(20 * DEG2RAD); // calculate initial player values
    raylib::Vector2 initPos = (raylib::Vector2){SCREEN_W / 2, SCREEN_H / 2 - initHeight / 2};
    raylib::Vector2 initVel = (raylib::Vector2){0.0f, 0.0f};
    raylib::Vector3 initCol = (raylib::Vector3){initPos.x + sin(0 * DEG2RAD) * (initHeight / 2.5f), initPos.y - cos(0 * DEG2RAD) * (initHeight / 2.5f), 12};

    ScoreManager scoreManager; // initialize score manager
    this->scoreManager = scoreManager;

    Player newPlayer; // initialize player
    this->player = newPlayer;
    this->player.setPosition(initPos); // set initial player object values
    this->player.setVelocity(initVel);
    this->player.setDirection(0.0f);
    this->player.setAcceleration(0.0f);
    this->player.setCollide(initCol);
    this->player.setHeight(initHeight);
    this->player.setHealth(100);

    for (int i = 0; i < MAX_ENEMIES; i++)
    {
        int posX = GetRandomValue(0, SCREEN_W); // calculate random X position for enemy
        while ((posX > SCREEN_W / 2 - 150) && (posX < SCREEN_W / 2 + 150))
        { // calculate until correct range
            posX = GetRandomValue(0, SCREEN_W);
        }

        int posY = GetRandomValue(0, SCREEN_H); // calculate random Y position for enemy
        while ((posY > SCREEN_H / 2 - 150) && (posY < SCREEN_H / 2 + 150))
        { // calculate until correct range
            posY = GetRandomValue(0, SCREEN_H);
        }

        int velX = GetRandomValue(-ENEMY_SPEED, ENEMY_SPEED); // calculate random velocity for enemy
        int velY = GetRandomValue(-ENEMY_SPEED, ENEMY_SPEED);
        while (velX == 0 && velY == 0)
        { // calculate until correct range
            int velX = GetRandomValue(-ENEMY_SPEED, ENEMY_SPEED);
            int velY = GetRandomValue(-ENEMY_SPEED, ENEMY_SPEED);
        }

        int randNum = GetRandomValue(0, 1); // calculate random direction for enemy

        // spawn either a small or normal enemy based on random number
        Enemy enemy; // initialize enemy object with values
        enemy.setPosition((raylib::Vector2){(float)posX, (float)posY});
        // enemy.setVelocity((raylib::Vector2){(float)velX, (float)velY});
        // set the velocity according to its radius
        enemy.setVelocity((raylib::Vector2){(float)velX * (4 / (enemy.getRadius() / 10)), (float)velY * (4 / (enemy.getRadius() / 10))});
        this->enemies[i] = enemy; // add to enemy list
    }
};


/**
 *   @brief      update game loops through game frames to allow for movement to occur and updates to be processed
 *               based on player health, if player is dead then game loop breaks
 *
 */
void Game::updateGame()
{
    if (gameOn)
    {
        if (IsKeyPressed(KEY_P))
            pauseGame();

        if (!gamePause)
        {
            rotation += 0.5f;
            if (this->player.getHealth() > 0) // if player is alive
            {
                this->player.move(); // move player position
                for (int i = 0; i < MAX_ENEMIES; i++)
                { // move alive enemy positions
                    if (this->enemies[i].getHealth() > 0)
                    {
                        this->enemies[i].move();
                    }
                };

                raylib::Vector3 newCol = (raylib::Vector3){this->player.getPosition().x + sin(this->player.getDirection() * DEG2RAD) * (this->player.getHeight() / 2.5f), this->player.getPosition().y - cos(this->player.getDirection() * DEG2RAD) * (this->player.getHeight() / 2.5f), 12};
                this->player.setCollide(newCol); // calculate new collide value for player
                for (int i = 0; i < MAX_ENEMIES; i++)
                { // check for collisions between player and enemies
                    if (this->enemies[i].getHealth() > 0)
                    {
                        if (CheckCollisionCircles((raylib::Vector2){this->player.getCollide().x, this->player.getCollide().y}, this->player.getCollide().z, this->enemies[i].getPosition(), this->enemies[i].getRadius()))
                        { // collision -> kill player
                            this->player.setHealth(-100);
                            if (this->scoreManager.getScore() > this->scoreManager.getHighScore())
                            { // update high score if achieved
                                this->scoreManager.setHighScore(this->scoreManager.getScore());
                            }
                            this->gameOn = false;
                        };
                    };
                };

                // basis to update score (around 3/4 of a frame)
                this->scoreManager.setFrames(1);
                if (this->scoreManager.getFrames() % 45 == 0)
                {
                    this->scoreManager.setScore(1);
                }
            }
            else
            { // player dead state
                if (this->scoreManager.getScore() > this->scoreManager.getHighScore())
                { // update high score if achieved
                    this->scoreManager.setHighScore(this->scoreManager.getScore());
                }

                if (IsKeyPressed(KEY_SPACE) || IsKeyPressed(KEY_ENTER))
                { // restart the game using space or enter key
                    this->gameOn = true;
                    startGame();
                }
            }
        }
    }
    else
    {
        if (IsKeyPressed(KEY_SPACE) || IsKeyPressed(KEY_ENTER))
        { // start the game using space or enter key
            this->gameOn = true;
            startGame();
        }
    }

    drawGame(); // redraw game
}


/**
 *   @brief      Draws visual objects on the game board
 *
 */
void Game::drawGame()
{
    BeginDrawing();

    ClearBackground(RAYWHITE);
    if (this->gameOn)
    { // if player is alive, draw game
        if (!this->gamePause)
        {
            raylib::Vector2 vector1 = {this->player.getPosition().x + sinf(this->player.getDirection() * DEG2RAD) * this->player.getHeight(), this->player.getPosition().y - cosf(this->player.getDirection() * DEG2RAD) * this->player.getHeight()};
            raylib::Vector2 vector2 = {this->player.getPosition().x - cosf(this->player.getDirection() * DEG2RAD) * (PLAYER_SIZE / 2), this->player.getPosition().y - sinf(this->player.getDirection() * DEG2RAD) * (PLAYER_SIZE / 2)};
            raylib::Vector2 vector3 = {this->player.getPosition().x + cosf(this->player.getDirection() * DEG2RAD) * (PLAYER_SIZE / 2), this->player.getPosition().y + sinf(this->player.getDirection() * DEG2RAD) * (PLAYER_SIZE / 2)};
            DrawTriangle(vector1, vector2, vector3, (raylib::Color){50, 255, 161}); // draw player object

            // big weapon upgrade
            if (this->scoreManager.getScore() % 100 >= 55 && this->activePowerup == false && this->player.checkIfBigActive() == false)
            {
                this->activePowerup = true;
                this->upgradeX = GetRandomValue(0, SCREEN_W);
                this->upgradeY = GetRandomValue(0, SCREEN_H);
                // Polygon shapes and lines
                DrawPoly((Vector2){this->upgradeX, this->upgradeY}, 4, 40, rotation, MAROON);
                DrawPolyLines((Vector2){this->upgradeX, this->upgradeY}, 4, 50, rotation, MAROON);
                DrawPolyLinesEx((Vector2){this->upgradeX, this->upgradeY}, 4, 55, rotation, 6, RED);
            }
            else if (this->activePowerup == true)
            {
                // Polygon shapes and lines
                DrawPoly((Vector2){this->upgradeX, this->upgradeY}, 4, 40, rotation, MAROON);
                DrawPolyLines((Vector2){this->upgradeX, this->upgradeY}, 4, 50, rotation, MAROON);
                DrawPolyLinesEx((Vector2){this->upgradeX, this->upgradeY}, 4, 55, rotation, 6, RED);
            }

            if (CheckCollisionPointCircle(this->player.getPosition(), (Vector2){this->upgradeX, this->upgradeY}, PLAYER_SIZE * 3) && this->player.checkIfBigActive() == false)
            {
                this->activePowerup = false;
                this->player.activateBigWeapon();
            }

            if (this->player.checkIfBigActive() == true)
            {
                this->bigWeaponCount += 1;
                if (this->bigWeaponCount > 250)
                {
                    this->player.deactivateBigWeapon();
                    this->bigWeaponCount = 0;
                }
            }

            for (int i = 0; i < MAX_ENEMIES; i++)
            { // draw all enemies
                if (CheckCollisionCircles(this->player.getWeapon().getPosition(), this->player.getWeapon().getRadius(), this->enemies[i].getPosition(), this->enemies[i].getRadius()) && this->enemies[i].getHealth() > 0)
                {
                    this->scoreManager.setScore((int)(this->enemies[i].getHealth() / 10));
                    this->enemies[i].setHealth(this->enemies[i].getHealth() - this->player.getWeapon().getDamage());
                    this->player.setWeaponUnactive();
                }
                if (this->enemies[i].getHealth() > 0)
                {
                    // draw the circle with a random color based on their radius, where the smaller the radius, the radius should determine the color from red to blue (ensure to cast the values)
                    DrawCircleV(this->enemies[i].getPosition(), this->enemies[i].getRadius(), (raylib::Color){(unsigned char)(255 - (this->enemies[i].getRadius() * 5)), 0, (unsigned char)(this->enemies[i].getRadius() * 5), 255});
                }
                else
                {
                    DrawCircleV(this->enemies[i].getPosition(), this->enemies[i].getRadius(), Fade(LIGHTGRAY, 0.3f));
                    if (this->enemies[i].getReviveCount() <= REVIVE_OUT)
                    {
                        this->enemies[i].addReviveCount();
                    }
                    else
                    {
                        this->enemies[i].setHealth(100);
                        int posX = GetRandomValue(0, SCREEN_W); // calculate random X position for enemy
                        while ((posX > SCREEN_W / 2 - 150) && (posX < SCREEN_W / 2 + 150))
                        { // calculate until correct range
                            posX = GetRandomValue(0, SCREEN_W);
                        }

                        int posY = GetRandomValue(0, SCREEN_H); // calculate random Y position for enemy
                        while ((posY > SCREEN_H / 2 - 150) && (posY < SCREEN_H / 2 + 150))
                        { // calculate until correct range
                            posY = GetRandomValue(0, SCREEN_H);
                        }

                        int velX = GetRandomValue(-ENEMY_SPEED, ENEMY_SPEED); // calculate random velocity for enemy
                        int velY = GetRandomValue(-ENEMY_SPEED, ENEMY_SPEED);
                        while (velX == 0 && velY == 0)
                        { // calculate until correct range
                            int velX = GetRandomValue(-ENEMY_SPEED, ENEMY_SPEED);
                            int velY = GetRandomValue(-ENEMY_SPEED, ENEMY_SPEED);
                        }
                        this->enemies[i].setPosition((raylib::Vector2){(float)posX, (float)posY});
                        this->enemies[i].setVelocity((raylib::Vector2){(float)velX, (float)velY});
                    }
                }
            };

            if (this->player.getWeapon().isActive())
            { // draw player weapon and play the sound
                DrawCircleV(this->player.getWeapon().getPosition(), this->player.getWeapon().getRadius(), SKYBLUE);
            }
        }
        else
        {
            DrawText("Ultra Super", SCREEN_W / 2 - MeasureText("Ultra Super", 75) / 2, SCREEN_H / 2 - 125, 75, DARKPURPLE);
            DrawText("Space Rocks", SCREEN_W / 2 - MeasureText("Space Rocks", 75) / 2, SCREEN_H / 2 - 50, 75, VIOLET);
            DrawText("Press [P] to resume the game.", SCREEN_W / 2 - MeasureText("Press [P] to resume the game.", 25) / 2, SCREEN_H / 2 + 50, 25, DARKGRAY);
        }

        DrawText(("Score: " + std::to_string(this->scoreManager.getScore())).data(), SCREEN_W / 2 - MeasureText(("Score: " + std::to_string(this->scoreManager.getScore())).data(), 20) / 2, SCREEN_H - 50, 20, DARKGRAY); // draw score
    }
    else
    { // player dead -> show instructions to restart game
        DrawText("Ultra Super", SCREEN_W / 2 - MeasureText("Ultra Super", 75) / 2, SCREEN_H / 2 - 125, 75, DARKPURPLE);
        DrawText("Space Rocks", SCREEN_W / 2 - MeasureText("Space Rocks", 75) / 2, SCREEN_H / 2 - 50, 75, VIOLET);
        DrawText("Press [SPACE] or [ENTER] to start the game.", SCREEN_W / 2 - MeasureText("Press [SPACE] or [ENTER] to start the game.", 25) / 2, SCREEN_H / 2 + 50, 25, DARKGRAY);
        // draw final score
        DrawText(("Previous Score: " + std::to_string(this->scoreManager.getScore())).data(), 25, SCREEN_H - 50, 20, DARKBLUE);
        DrawText(("High Score: " + std::to_string(this->scoreManager.getHighScore())).data(), SCREEN_W - MeasureText(("High Score: " + std::to_string(this->scoreManager.getHighScore())).data(), 20) - 25, SCREEN_H - 50, 20, DARKBLUE);
    }

    EndDrawing();
}


/**
 *   @brief      pauses game and allows player to choose when to continue
 *
 */
void Game::pauseGame()
{
    this->gamePause = !gamePause; //update boolean
}