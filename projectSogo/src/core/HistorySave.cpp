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

void HistorySave::AddMove(Move *move)
{
    this->m_pastMoves->push_back(move);
}

void HistorySave::RevertLast()
{
    this->m_pastMoves->erase(this->m_pastMoves->end());
}

/**
 * @brief GetMoveCount
 * @return
 */
int HistorySave::GetMoveCount() const
{
    return this->m_pastMoves->size();
}

/**
 * @brief GetMove
 * @param number
 * @return
 */
const HistorySave::Move *HistorySave::GetMove(int number) const throw(out_of_range)
{
    return m_pastMoves->at(number);
}

/**
 * @brief GetLastMove
 * @return
 */
const HistorySave::Move *HistorySave::GetLastMove() const throw(out_of_range)
{
    return m_pastMoves->at(m_pastMoves->size() - 1);
}


string HistorySave::Serialize(const HistorySave& save)
{
    stringstream s;


    //trenner #

    for(int i = 0; i < save.GetMoveCount(); i++)
    {
        s << Move::Serialize(save.GetMove(i)) << "#";
    }

    return s.str();
}

bool HistorySave::Deserialize(string str, HistorySave *save)
{
    std::vector<string> elems;

    Logger::GetLoggerIntance()->LogInfo(str, __FILE__, __LINE__);

    split(str, delimiter, elems);

    bool worked = true;

    Move *tempMove;

    HistorySave *tempSave = new HistorySave();

    for(int i = 0; i < elems.size(); i++)
    {


        if(!Move::Deserialize(elems.at(i), tempMove))
        {
            Logger::GetLoggerIntance()->LogInfo("HistorySave Deserializierung Move Failed", __FILE__, __LINE__);
            worked = false;
            break;
        }

        tempSave->AddMove(tempMove);

    }


    if(worked)
    {
        save = tempSave;
    }
    else
    {
        delete(tempSave);
    }

    return worked;
}
