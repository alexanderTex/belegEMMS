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
 * skill ( currently only effectively used by ai)
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
        HUMAN,
        AI,
    };

    /**
     * @brief Player
     * @param type
     * @param name
     * @param color
     * @param skill
     */
    Player(PlayerType type, std::string name, PlayingField::OccupationState color, int skill = 1);

    /**
     * @brief Player
     * @param src
     */
    Player(const Player &src);

    /**
     * @brief GetType
     * @return
     */
    inline PlayerType GetType() const
    {
        return m_playerType;
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

    /**
     * @brief SetName
     * @param name
     */
    inline void SetName(std::string name)
    {
        m_playerName = name;
    }

    /**
     * @brief GetSkill
     * @return
     */
    inline int GetSkill() const
    {
        return m_playerSkill;
    }

    /**
     * @brief SetSkill
     * @param skill
     */
    inline void SetSkill(int skill)
    {
        m_playerSkill = skill;
    }

private:
    /**
     * @brief m_type
     */
    PlayerType m_playerType;
    /**
     * @brief m_playerName
     */
    std::string m_playerName;
    /**
     * @brief m_playerColor
     */
    PlayingField::OccupationState m_playerColor;
    /**
     * @brief m_skill
     */
    int m_playerSkill;

};

#endif // PLAYER_H
