#include "GameManagerThread.h"

#include <stdio.h>
#include <iostream>
#include "PlayingField.h"

GameManager::GameManager()
{
    this->m_data = NULL;
    m_stopThreadExecution = false;
    m_endGame = false;
    m_paused = true;
    this->m_playerInputConfirmed = false;
    this->start();
}

GameManager::GameManager( GameData *data)
{
    this->m_data = data;
    m_stopThreadExecution = false;
    m_endGame = false;
    m_paused = true;
    this->m_playerInputConfirmed = false;
    this->start();
}

GameManager::~GameManager()
{
    Logger::GetLoggerIntance()->LogInfo("GameLoop deleted");
}

void GameManager::run()
{
    this->GameLoop();
}

/**
 * @brief GetGameData
 * @return
 */
const GameData *GameManager::GetGameData() const
{
    return this->m_data;
}

/**
 * @brief SetGameData
 */
void GameManager::SetGameData(GameData * data)
{
    this->m_data = data;
    m_endGame = false;
}

void GameManager::StartGame()
{
    m_paused = false;
    m_endGame = false;
}


void GameManager::PauseGame()
{
    m_paused = true;
}

void GameManager::SuspendProcessingLoop()
{
    m_endGame = true;
}

/**
 * @brief Stop
 * sets the boolean to end the Main processing thread when the user quits the game
 */
void GameManager::StopGameManagerThread()
{
    m_endGame = true;
    m_stopThreadExecution = true;
}

/**
 * @brief InputConfirmationDetected
 * @param pos
 */
void GameManager::InputConfirmationDetected(Vector2 pos)
{
    playerPosChoice = pos;

    std::stringstream s;
    s << pos.X << " : " << pos.Y;
    Logger::GetLoggerIntance()->LogInfo(s.str(), __FILE__, __LINE__);

    m_playerInputConfirmed = true;
}


bool GameManager::MakeMove(Vector3 pos) throw(PlayingField::FieldExeptions, std::out_of_range)
{
    this->m_data->OccupySlot(pos.X, pos.Y, pos.Z, this->m_data->GetCurrentPlayer()->GetColor());


    if(CheckForWin(this->m_data->GetField(), this->m_data->GetCurrentPlayer()->GetColor()))
    {
        //end game event
        return true;
    }

    this->m_data->SwitchPlayer();
    return false;
}

void GameManager::GameLoop()
{

    Logger::GetLoggerIntance()->LogInfo("GameLoop startet :" );

    bool currentPlayerMoveReady = false;
    Vector3 pos;



    while(m_stopThreadExecution == false)
    {
        while(m_endGame == false)
        {
            //Logger::GetLoggerIntance()->LogInfo("GameLoop running...");
            InputRoutine(currentPlayerMoveReady, &pos);

            if(currentPlayerMoveReady)
            {
                try
                {
                    if(this->MakeMove(pos))
                    {
                        TurnFinished();
                        emit PlayerWon();
                        this->m_endGame = true;
                    }
                    else
                    {
                        TurnFinished();

                        PlayInputAcceptSound();
                    }
                }
                catch(PlayingField::FieldExeptions e)
                {
                    Logger::GetLoggerIntance()->LogError("Input not Valid");
                    if(e == PlayingField::NO_SPACE_ANYMORE)
                    {
                        this->m_endGame = true;
                        // send signal to indicate draw
                    }
                }
                catch(std::out_of_range e)
                {
                    Logger::GetLoggerIntance()->LogError("Input Out of Range");
                    this->m_endGame = true;
                }

                currentPlayerMoveReady = false;
            }

        }
        Logger::GetLoggerIntance()->LogInfo("GameManager Loop waiting");
    }
    Logger::GetLoggerIntance()->LogInfo("GameManager Loop stopped");
}


void GameManager::InputRoutine(bool &currentPlayerMoveReady, Vector3 *pos) throw(out_of_range, PlayingField::FieldExeptions)
{
    if(!m_paused)
    {
        if(this->m_data != NULL)
        {

            if(this->m_data->GetCurrentPlayer()->GetType() == Player::HUMAN)
            {
                //wait for input accepted
                // if accepted do input conformed process
                if(this->m_playerInputConfirmed)
                {
                    try
                    {
                        currentPlayerMoveReady = PlayerInputProcess(pos);
                    }
                    catch(PlayingField::FieldExeptions e)
                    {
                        Logger::GetLoggerIntance()->LogError("Player Input not Valid");
                        // Play Bad Input sound
                        currentPlayerMoveReady = false;

                        PlayInputErrorSound();

                    }
                    catch(std::out_of_range e)
                    {
                        Logger::GetLoggerIntance()->LogError("Player Input Out of Range");
                        // Play Bad Input sound
                        currentPlayerMoveReady = false;

                        PlayInputErrorSound();
                    }

                    this->m_playerInputConfirmed = false;
                }
            }
            else
            {
                currentPlayerMoveReady = AIProcess(m_data->GetCurrentPlayer(), pos);
            }

        }
    }
}

bool GameManager::PlayerInputProcess(Vector3 *pos) throw(out_of_range, PlayingField::FieldExeptions)
{

    Logger::GetLoggerIntance()->LogInfo("PlayerInput start");
    int z = GetAvailablePosition(this->playerPosChoice.X, this->playerPosChoice.Y, this->GetGameData()->GetField());

    if(z >= 0)
        Logger::GetLoggerIntance()->LogInfo("PlayerInput Input available");
    else
        Logger::GetLoggerIntance()->LogInfo("PlayerInput Input not available");

    pos->X = this->playerPosChoice.X;
    pos->Y = this->playerPosChoice.Y;
    pos->Z = z;
    Logger::GetLoggerIntance()->LogInfo("PlayerInput assigned");
    return true;


}

bool GameManager::AIProcess(Player *player, Vector3 *move)
{
    if(player != NULL)
    {
        if(this->m_data->GetCurrentPlayer() == player)
        {
            const Player *opponent = this->m_data->GetOpponent(player);


            MiniMax(this->m_data->GetField(), player->GetColor(), player->GetColor(), player->GetSkill(), move);

            return true;
        }

    }
    return false;
}
