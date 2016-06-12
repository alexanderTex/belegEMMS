#include "GameManagerThread.h"

#include <stdio.h>
#include <iostream>
#include "PlayingField.h"

GameManager::GameManager( GameData *data)
{
    this->m_data = data;
    m_stop = false;
    this->m_playerInputConfirmed = false;
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

    vector<Vector3> *possibleOpponentMoves;
    vector<Vector3> *futureMoves = new vector<Vector3>();

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



    while(m_stop == false && this->m_data != NULL)
    {
        if(this->m_data->GetCurrentPlayer()->GetType() == Player::Human)
        {
            //wait for input accepted
            // if accepted do input conformed process
            if(this->m_playerInputConfirmed)
            {
                try
                {
                    Vector3 pos(this->playerPosChoice.X, this->playerPosChoice.Y, GetAvailablePosition(this->playerPosChoice.X, this->playerPosChoice.Y, this->GetGameData()->GetField()));

                    if(MakeMove(pos))
                    {
                        TurnFinished();
                        emit PlayerWon();
                    }
                    else
                    {
                        TurnFinished();
                    }
                    Logger::GetLoggerIntance()->LogInfo("PlayerInput Applied");

                }
                catch(PlayingField::FieldExeptions)
                {
                    Logger::GetLoggerIntance()->LogError("Input not Valid");
                }
                catch(std::out_of_range)
                {
                    Logger::GetLoggerIntance()->LogError("Input Out of Range");
                }

                this->m_playerInputConfirmed = false;
            }
        }


        AIProcess(aiPlayer1);
        AIProcess(aiPlayer2);


        if(this->m_stop)
        {
            Logger::GetLoggerIntance()->LogInfo("GameManager Loop stopped");
        }
    }    
}

void GameManager::AIProcess(AIPlayer *ai)
{
    if(ai != NULL)
    {
        if(ai->hasMove == false)
        {
           /*
            Logger::GetLoggerIntance()->Log(DrawPlayingField(data->GetField()));

            Logger::GetLoggerIntance()->LogInfo("Calculating...");
            Logger::GetLoggerIntance()->Log("\n" );

            possibleOpponentMoves = GetAvailablePositions(data->GetField());

            stringstream possiblePosSize;

            possiblePosSize << possibleOpponentMoves->size() << endl;

            Logger::GetLoggerIntance()->LogInfo(possiblePosSize.str());

            if(futureMoves == NULL)
            {
                futureMoves = new vector<Vector3>();
            }

            for(int i = 0; i < possibleOpponentMoves->size(); i++)
            {
                Vector3 futuremove;
                PlayingField p(data->GetField());
                p.OccupySlot(possibleOpponentMoves->at(i), opponent->GetColor());

                MiniMax(data->GetField(), player->GetColor(), player->GetColor(), 3, &futuremove);
                futureMoves->push_back(futuremove);


                stringstream s;
                s << i << " calculated!" << endl;

                Logger::GetLoggerIntance()->LogInfo(s.str());
            }

            stringstream s;

            s << "Calculating finished" << endl;
            Logger::GetLoggerIntance()->LogInfo(s.str());

            */

            ai->hasMove = true;
        }

        if(ai->hasMove == true && this->m_data->GetCurrentPlayer() == ai->player)
        {
            const Player *opponent = this->m_data->GetOpponent(ai->player);

            Vector3 futuremove;

            MiniMax(this->m_data->GetField(), ai->player->GetColor(), ai->player->GetColor(), 4, &futuremove);


            /*
            stringstream check;
            check << "Checking moves" << endl;
            Logger::GetLoggerIntance()->LogInfo(check.str());

            int i = -1;
            for( i = 0; i < possibleOpponentMoves->size(); i++)
            {
                if(*(data->GetLastMove()) == possibleOpponentMoves->at(i))
                {
                    break;
                }
            }
            */


            try
            {
                if(this->MakeMove(futuremove))
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




            ai->hasMove = false;


            //delete(futureMoves);
            //delete(possibleOpponentMoves);

        }
    }
}
