#include "../../include/core/GameData.h"

GameData::GameData(PlayingField *field, PlayingField::OccupationState player)
{
    this->m_field = field;
    this->m_currentPlayer = player;

}

void GameData::MakeMove(const Vector2*pos)
{
    try
    {
        this->m_field->OccupySlot(pos->X, pos->Y, this->m_currentPlayer);

        if(CheckForWin(this->m_field, this->m_currentPlayer))
        {
            //end game event
        }

        this->m_currentPlayer = this->m_currentPlayer == PlayingField::Blue ? PlayingField::Red : PlayingField::Blue;

        this->NotifyAllObserver();
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
}
