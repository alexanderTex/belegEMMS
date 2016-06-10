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
    this->AILoop();
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

void GameManager::AILoop()
{
    Logger::GetLoggerIntance()->LogInfo("GameLoop startet :" );
    Logger::GetLoggerIntance()->Log("\n" );

    vector<Vector3> *possibleOpponentMoves;
    vector<Vector3> *futureMoves = new vector<Vector3>();

    AI *aiPlayer1 = NULL;



    if(this->m_data->GetPlayer1()->GetType() == Player::Ai)
    {
        aiPlayer1 = new AI(this->m_data->GetPlayer1());
    }

    AI *aiPlayer2 = NULL;

    if(this->m_data->GetPlayer2()->GetType() == Player::Ai)
    {
        aiPlayer2 = new AI(this->m_data->GetPlayer2());
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
                        InputMade();
                        emit PlayerWon();
                    }
                    else
                    {
                        InputMade();
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

        if(aiPlayer1 != NULL)
        {
            if(aiPlayer1->hasMove == false)
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

                aiPlayer1->hasMove = true;
            }
            if(aiPlayer1->hasMove == true && this->m_data->GetCurrentPlayer() == aiPlayer1->player)
            {
                const Player *opponent = this->m_data->GetOpponent(aiPlayer1->player);

                Vector3 futuremove;

                MiniMax(this->m_data->GetField(), aiPlayer1->player->GetColor(), aiPlayer1->player->GetColor(), 4, &futuremove);

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
                        AITurnFinished();
                        emit AIWon();
                        this->m_stop = true;
                    }
                    else
                    {
                        AITurnFinished();
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




                aiPlayer1->hasMove = false;



                //delete(futureMoves);
                //delete(possibleOpponentMoves);

            }
        }

        if(aiPlayer2 != NULL)
        {
            if(aiPlayer2->hasMove == false)
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

                aiPlayer2->hasMove = true;
            }

            if(aiPlayer2->hasMove == true && this->m_data->GetCurrentPlayer() == aiPlayer2->player)
            {
                const Player *opponent = this->m_data->GetOpponent(aiPlayer2->player);

                Vector3 futuremove;

                MiniMax(this->m_data->GetField(), aiPlayer2->player->GetColor(), aiPlayer2->player->GetColor(), 4, &futuremove);


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
                        AITurnFinished();
                        emit AIWon();
                        this->m_stop = true;
                    }
                    else
                    {
                        AITurnFinished();
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




                aiPlayer2->hasMove = false;


                //delete(futureMoves);
                //delete(possibleOpponentMoves);

            }
        }

        if(this->m_stop)
        {
            Logger::GetLoggerIntance()->LogInfo("GameManager Loop stopped");
        }
    }    
}
