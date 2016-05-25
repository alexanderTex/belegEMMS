#ifndef PLAYER_H
#define PLAYER_H

#include <string>

#include "PlayingField.h"

class Player
{
public:
    enum PlayerType
    {
        Human,
        Ai,
    };

    Player(PlayerType type, std::string name, PlayingField::OccupationState color);

    inline PlayerType GetType() const
    {
        return m_type;
    }

    inline std::string GetName() const
    {
        return m_PlayerName;
    }

    inline PlayingField::OccupationState GetColor() const
    {
        return m_PlayerColor;
    }

private:
    PlayerType m_type;
    std::string m_PlayerName;
    PlayingField::OccupationState m_PlayerColor;
};

#endif // PLAYER_H
