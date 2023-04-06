/**
 *   @brief      score manager keeps an object to track the score of the game
 *               the score is initalized and cna be updated based on # of frames
 *   @authors    Gurshawn Lehal, Imesh Nimsitha, Gunveer Vilkhu 
 */

#include "scoremanager.hpp"


/**
 *   @brief      Constructor object for the score manager
 *               creates the object and initalizes score to 0, and loads highscore
 */
ScoreManager::ScoreManager()
{
    this->score = 0;
    this->highScore = load(0);

    if (this->highScore == 0) //load highscore
    {
        setHighScore(0);
    }
}


/**
 *   @brief      deconstructor object for the score manager
 *               cleans up any objects to be destroyed 
 */
ScoreManager::~ScoreManager()
{
}


/**
 *   @brief      getScore grabs the score value of the object and returns it
 *   @return     the int value of the score
 */
int ScoreManager::getScore()
{
    return this->score;
}


/**
 *   @brief      set Score adds a value to current score and updates it
 *   @param      modifer the value to be set for the score
 */
void ScoreManager::setScore(int modifier)
{
    this->score += modifier;
}


/**
 *   @brief      getHighscore returns the highscore of the game so far
 *   @return     int the int value of the highscore
 */
int ScoreManager::getHighScore()
{
    return this->highScore;
}


/**
 *   @brief      set Score adds a value to current highscore and updates it
 *   @param      newHigh the value to be set for the highscore
 */
void ScoreManager::setHighScore(int newHigh)
{
    save(0, newHigh); //save the score
    this->highScore = newHigh;
}


/**
 *   @brief      get frames get the frame settings in the game
 *   @return     int the # of frames
 */
int ScoreManager::getFrames()
{
    return this->frames;
}


/**
 *   @brief      set frames for the game, updates based on current frames
 *   @param modifier     the # of frames to be set
 */
void ScoreManager::setFrames(int modifier)
{
    this->frames += modifier;
}

/**
 *   @brief      load, loads the score manager to its intial state
 *   @param      position the value to look for
 *   @return     int, the value of the file located at position
 */
int ScoreManager::load(int position)
{
    int value = 0; //intialize lookup
    unsigned int dataSize = 0;
    unsigned char *fileData = LoadFileData(FILE_DATA, &dataSize);

    if (fileData != NULL) //check for load 
    {
        if (dataSize >= (position * 4))
        {
            int *dataPtr = (int *)fileData;
            value = dataPtr[position];
        }
        UnloadFileData(fileData);
    }

    return value;
}


/**
 *   @brief      saves the score at the position located
 *   @param      position the area to be saved to
 *   @param      value the value to be saved at the position
 *   @return     successful save
 */
bool ScoreManager::save(int position, int value)
{
    bool success = false; //check for succesful save
    unsigned int dataSize = 0; //file load check
    unsigned int newDataSize = 0;
    unsigned char *fileData = LoadFileData(FILE_DATA, &dataSize);
    unsigned char *newFileData = NULL;

    if (fileData != NULL) //if file exists
    {
        if (dataSize <= (position * sizeof(int))) //if file can hold number
        {
            newDataSize = (position + 1) * sizeof(int); // Increase data size up to position and store value
            newFileData = (unsigned char *)RL_REALLOC(fileData, newDataSize);

            if (newFileData != NULL)
            {
                int *dataPtr = (int *)newFileData; // RL_REALLOC succeded
                dataPtr[position] = value;
            }
            else
            {
                newFileData = fileData; // We store the old size of the file
                newDataSize = dataSize;
            }
        }
        else
        {
            newFileData = fileData; // Store the old size of the file
            newDataSize = dataSize;

            int *dataPtr = (int *)newFileData; // Replace value on selected position
            dataPtr[position] = value;
        }

        success = SaveFileData(FILE_DATA, newFileData, newDataSize); //check if save was successful
        RL_FREE(newFileData);
    }
    else
    {
        dataSize = (position + 1) * sizeof(int); //create new file
        fileData = (unsigned char *)RL_MALLOC(dataSize);
        int *dataPtr = (int *)fileData;
        dataPtr[position] = value;

        success = SaveFileData(FILE_DATA, fileData, dataSize); //success
        UnloadFileData(fileData);
    }

    return success;
}
