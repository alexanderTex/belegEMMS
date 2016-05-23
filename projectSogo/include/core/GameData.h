#ifndef GAMEDATA_H
#define GAMEDATA_H

#include <stdexcept>

#include "../include/core/PlayingField.h"
#include "../include/core/Vector2.h"
#include "../include/utility/Logger.h"
#include "../include/Subject.h"

class GameData : public Subject
{
public:
    GameData(PlayingField *field, PlayingField::OccupationState player);
    virtual ~GameData();


    inline const PlayingField *GetField() const
    {
        return m_field;
    }

    inline PlayingField::OccupationState GetCurrentPlayer() const
    {
        return m_currentPlayer;
    }

    inline void SetCurrentPlayer(PlayingField::OccupationState player)
    {
        m_currentPlayer = player;
    }

    void MakeMove(const Vector2*pos);


private:
    PlayingField *m_field;
    PlayingField::OccupationState m_currentPlayer;
};

#endif // GAMEDATA_H
