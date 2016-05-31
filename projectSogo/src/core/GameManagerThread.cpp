#include "GameManagerThread.h"

#include <stdio.h>
#include <iostream>
#include "PlayingField.h"

void AILoop(const Player *player, GameData *data)
{
    Logger::GetLoggerIntance()->LogInfo("GameLoop startet :" );
    Logger::GetLoggerIntance()->Log("\n" );

    vector<Vector3> *possibleOpponentMoves;
    vector<Vector3> *futureMoves = new vector<Vector3>();

    bool needNewMove = true;

    Player *opponent = data->GetOpponent(player);

    while(data != NULL)
    {
        if(needNewMove == true)
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

            needNewMove = false;
        }
        if(data->GetCurrentPlayer() == player && needNewMove == false)
        {
            Vector3 futuremove;

            MiniMax(data->GetField(), player->GetColor(), player->GetColor(), 3, &futuremove);

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

            stringstream s;
            s << "Making move" << endl;
            Logger::GetLoggerIntance()->LogInfo(s.str());

            try
            {
                data->MakeMove(futuremove);
            }
            catch(PlayingField::FieldExeptions e)
            {
                Logger::GetLoggerIntance()->LogError("Input not Valid");
            }
            catch(std::out_of_range e)
            {
                Logger::GetLoggerIntance()->LogError("Input Out of Range");
            }

            stringstream stream2;
            stream2 << "Move done" << endl;
            Logger::GetLoggerIntance()->LogInfo(stream2.str());


            needNewMove = true;



            //delete(futureMoves);
            //delete(possibleOpponentMoves);

        }
    }
}
