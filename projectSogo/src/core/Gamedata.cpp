#include "../../include/core/GameData.h"

GameData::GameData(PlayingField *field, Player *p1, Player *p2, Player *startingPlayer)
{
    this->m_field = field;
    this->player1 = p1;
    this->player2 = p2;
    this->m_currentPlayer = startingPlayer;
}

void GameData::MakeMove(Vector3 pos)
{        
    try
    {
        this->m_field->OccupySlot(pos.X, pos.Y, pos.Z, this->m_currentPlayer->GetColor());

        if(CheckForWin(this->m_field, this->m_currentPlayer->GetColor()))
        {
            //end game event
            stringstream s;
            s << this->m_currentPlayer->GetName() << " WON!" << std::endl;
            Logger::GetLoggerIntance()->LogInfo(s.str());
        }

        this->SwitchPlayer();
    }
    catch(PlayingField::FieldExeptions)
    {
        Logger::GetLoggerIntance()->LogError("Input not Valid");
    }
    catch(std::out_of_range)
    {
        Logger::GetLoggerIntance()->LogError("Input Out of Range");
    }
}

GameData::~GameData()
{
    delete(m_field);
    delete(player1);
    delete(player2);
}
