#include "HistorySave.h"

HistorySave::HistorySave()
{
    this->m_pastMoves = new std::vector<Move *>();
}

HistorySave::~HistorySave()
{
    for(int i = 0; i < this->m_pastMoves->size(); i++)
    {
        delete( this->m_pastMoves->at(i));
    }
    delete(this->m_pastMoves);
}


void HistorySave::AddMove(Vector3 pos, Player player)
{
    this->m_pastMoves->push_back(new HistorySave::Move(pos, player));
}

void HistorySave::RevertLast()
{
    this->m_pastMoves->erase(this->m_pastMoves->end());
}
