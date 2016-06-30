#include "HistorySave.h"

HistorySave::Move::Move(const Move* src)
{
    this->position = new Vector3(*(src->position));
    this->player = new Player(*(src->player));
}

HistorySave::Move::~Move()
{
    delete(position);
    delete(player);
}



HistorySave::HistorySave()
{
    this->m_pastMoves = new std::vector<Move *>();
}

HistorySave::HistorySave(const HistorySave &src)
{
    this->m_pastMoves = new std::vector<Move *>();
    for(int i = 0; i < src.m_pastMoves->size(); i++)
    {
        this->m_pastMoves->push_back(new Move(src.m_pastMoves->at(i)));
    }
}

HistorySave::~HistorySave()
{
    for(int i = 0; i < this->m_pastMoves->size(); i++)
    {
        delete(this->m_pastMoves->at(i));
    }
    delete(this->m_pastMoves);
}


void HistorySave::AddMove(Vector3 pos, Player player)
{
    this->m_pastMoves->push_back(new HistorySave::Move(new Vector3(pos), new Player(player)));
}

void HistorySave::RevertLast()
{
    this->m_pastMoves->erase(this->m_pastMoves->end());
}
