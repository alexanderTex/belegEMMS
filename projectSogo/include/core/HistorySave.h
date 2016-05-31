#ifndef HISTORYSAVE_H
#define HISTORYSAVE_H

#include <vector>
#include "Vector3.h"
#include "Player.h"

class HistorySave
{


    struct Move
    {
        Move(Vector3 pos, Player player)
        {
            this->position = &pos;
            this->player = &player;
        }

        Vector3 *position;
        Player *player;
    };

public:

    HistorySave();
    ~HistorySave();

    void AddMove(Vector3 pos, Player player);
    void RevertLast();

    inline const Move *GetMove(int number) throw(out_of_range)
    {
        return m_pastMoves->at(number);
    }

    inline const Move *GetLastMove() throw(out_of_range)
    {
        return m_pastMoves->at(m_pastMoves->size() - 1);
    }

private:
    std::vector< Move * > *m_pastMoves;
};

#endif // HISTORYSAVE_H
