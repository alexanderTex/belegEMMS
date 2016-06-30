#include "GameManagerThread.h"

#include <stdio.h>
#include <iostream>
#include "PlayingField.h"

GameManager::GameManager()
{
    this->m_data = NULL;
    m_stop = false;
    m_paused = true;
    this->m_playerInputConfirmed = false;
    this->start();
}

GameManager::GameManager( GameData *data)
{
    this->m_data = data;
    m_stop = false;
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
    Logger::GetLoggerIntance()->Log("\n" );

    AIPlayer *aiPlayer1 = NULL;



    if(this->m_data->GetPlayer1()->GetType() == Player::Ai)
    {
        aiPlayer1 = new AIPlayer(this->m_data->GetPlayer1());
    }

    AIPlayer *aiPlayer2 = NULL;

    if(this->m_data->GetPlayer2()->GetType() == Player::Ai)
    {
        aiPlayer2 = new AIPlayer(this->m_data->GetPlayer2());
    }

    bool currentPlayerMoveReady = false;
    Vector3 *pos = new Vector3();

    while(m_stop == false)
    {

        if(this->m_data != NULL)
        {
            if(this->m_data->GetCurrentPlayer()->GetType() == Player::Human)
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
                    }
                    catch(std::out_of_range e)
                    {
                        Logger::GetLoggerIntance()->LogError("Player Input Out of Range");
                        // Play Bad Input sound
                    }

                    this->m_playerInputConfirmed = false;
                }
            }

            if(!m_paused && !currentPlayerMoveReady)
            {
                currentPlayerMoveReady = AIProcess(aiPlayer1, pos) || AIProcess(aiPlayer2, pos);
            }


            if(currentPlayerMoveReady)
            {
                Logger::GetLoggerIntance()->LogInfo("Currentplayer moves start");
                try
                {
                    if(this->MakeMove(*pos))
                    {
                        TurnFinished();
                        emit PlayerWon();
                        this->m_stop = true;
                    }
                    else
                    {
                        TurnFinished();
                    }
                }
                catch(PlayingField::FieldExeptions e)
                {
                    Logger::GetLoggerIntance()->LogError("Input not Valid");
                    this->m_stop = true;
                }
                catch(std::out_of_range e)
                {
                    Logger::GetLoggerIntance()->LogError("Input Out of Range");
                    this->m_stop = true;
                }

                currentPlayerMoveReady = false;
            }
         }

        if(this->m_stop)
        {
            Logger::GetLoggerIntance()->LogInfo("GameManager Loop stopped");
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

bool GameManager::AIProcess(AIPlayer *ai, Vector3 *move)
{
    if(ai != NULL)
    {
        if(this->m_data->GetCurrentPlayer() == ai->player)
        {
            const Player *opponent = this->m_data->GetOpponent(ai->player);



            MiniMax(this->m_data->GetField(), ai->player->GetColor(), ai->player->GetColor(), 4, move);

            return true;
        }

    }
    return false;
}
