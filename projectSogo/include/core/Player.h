#ifndef PLAYER_H
#define PLAYER_H

#include <string>

#include "PlayingField.h"

/**
 * @brief The Player class
 * Defines a Player that is defined by
 * the type, which the player belongs to ( human or ai player )
 * a name
 * a Color ( Currently Occupationstate )
 */
class Player
{
public:
    /**
     * @brief The PlayerType enum
     * defines which type the player can be of
     * who is playing the game
     */
    enum PlayerType
    {
        Human,
        Ai,
    };

    /**
     * @brief Player
     * @param type
     * @param name
     * @param color
     */
    Player(PlayerType type, std::string name, PlayingField::OccupationState color);

    /**
     * @brief GetType
     * @return
     */
    inline PlayerType GetType() const
    {
        return m_type;
    }

    /**
     * @brief GetName
     * @return
     */
    inline std::string GetName() const
    {
        return m_playerName;
    }

    /**
     * @brief GetColor
     * @return
     */
    inline PlayingField::OccupationState GetColor() const
    {
        return m_playerColor;
    }

private:
    PlayerType m_type;
    std::string m_playerName;
    PlayingField::OccupationState m_playerColor;
};

#endif // PLAYER_H
