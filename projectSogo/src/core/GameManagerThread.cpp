#include "GameManagerThread.h"

#include <stdio.h>
#include <iostream>
#include "PlayingField.h"

AIGameLoop::AIGameLoop( GameData *data)
{
    this->m_data = data;
    m_stop = false;
}

AIGameLoop::~AIGameLoop()
{
    Logger::GetLoggerIntance()->LogInfo("GameLoop deleted");
}

void AIGameLoop::run()
{
    this->AILoop();
}

void AIGameLoop::AILoop()
{
    Logger::GetLoggerIntance()->LogInfo("GameLoop startet :" );
    Logger::GetLoggerIntance()->Log("\n" );

    vector<Vector3> *possibleOpponentMoves;
    vector<Vector3> *futureMoves = new vector<Vector3>();

    AI *aiPlayer1;

    if(this->m_data->GetPlayer1()->GetType() == Player::Ai)
    {
        aiPlayer1 = new AI(this->m_data->GetPlayer1());
    }

    AI *aiPlayer2;

    if(this->m_data->GetPlayer2()->GetType() == Player::Ai)
    {
        aiPlayer2 = new AI(this->m_data->GetPlayer2());
    }



    while(m_stop == false && (this->m_data != NULL && (aiPlayer1 != NULL || aiPlayer2 != NULL)))
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
            Player *opponent = this->m_data->GetOpponent(aiPlayer1->player);

            Vector3 futuremove;

            MiniMax(this->m_data->GetField(), aiPlayer1->player->GetColor(), aiPlayer1->player->GetColor(), 3, &futuremove);

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
                if(this->m_data->MakeMove(futuremove))
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
            Player *opponent = this->m_data->GetOpponent(aiPlayer2->player);

            Vector3 futuremove;

            MiniMax(this->m_data->GetField(), aiPlayer2->player->GetColor(), aiPlayer2->player->GetColor(), 3, &futuremove);


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
                if(this->m_data->MakeMove(futuremove))
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

        if(this->m_stop)
        {
            Logger::GetLoggerIntance()->LogInfo("Thread stopped");
        }
        else
        {
            Logger::GetLoggerIntance()->LogInfo("Thread running...");
        }
    }    
}
