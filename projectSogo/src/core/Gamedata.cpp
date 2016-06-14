#include "../../include/core/GameData.h"

GameData::GameData(PlayingField *field, Player *p1, Player *p2, Player *startingPlayer)
{
    this->m_field = field;
    this->m_player1 = p1;
    this->m_player2 = p2;
    this->m_currentPlayer = startingPlayer;
    this->m_history = new HistorySave();
}

GameData::GameData(const GameData *src)
{
    this->m_field = new PlayingField(src->GetField());
    this->m_history = new HistorySave(src->GetHistory());
    this->m_player1 = new Player(src->GetPlayer1());
    this->m_player2 = new Player(GetPlayer2());
    this->m_currentPlayer = src->GetCurrentPlayer()->GetColor() == this->m_player1->GetColor() ? this->m_player1 : this->m_player2;
}

GameData::~GameData()
{
    delete(m_field);
    delete(m_player1);
    delete(m_player2);
    delete(m_history);
}
