#include "../../include/core/GameData.h"

GameData::GameData(PlayingField *field, Player *p1, Player *p2, Player *startingPlayer)
{
    this->m_field = field;
    this->m_player1 = p1;
    this->m_player2 = p2;
    this->m_currentPlayer = startingPlayer;
    this->m_history = new HistorySave();
}

void GameData::MakeMove(Vector3 pos) throw(PlayingField::FieldExeptions, std::out_of_range)
{
    this->m_field->OccupySlot(pos.X, pos.Y, pos.Z, this->m_currentPlayer->GetColor());

    if(CheckForWin(this->m_field, this->m_currentPlayer->GetColor()))
    {
        //end game event
        stringstream s;
        s << this->m_currentPlayer->GetName() << " WON!" << std::endl;
        Logger::GetLoggerIntance()->Log(s.str());
    }
    this->m_history->AddMove(pos, *(this->GetCurrentPlayer()));

    stringstream s;
    s << this->m_currentPlayer->GetName() << " set a piece at " << pos.X << " " << pos.Y << " " << pos.Z << std::endl;
    Logger::GetLoggerIntance()->LogInfo(s.str());

    this->SwitchPlayer();
}

GameData::~GameData()
{
    delete(m_field);
    delete(m_player1);
    delete(m_player2);
    delete(m_history);
}
