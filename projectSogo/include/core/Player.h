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
    Player(PlayerType type, std::string name, PlayingField::OccupationState color, unsigned int skill = 0);

    /**
     * @brief Player
     * @param src
     */
    Player(const Player &src);

    /**
     * @brief GetType
     * @return
     */
    PlayerType GetType() const;

    /**
     * @brief GetName
     * @return
     */
    std::string GetName() const;

    /**
     * @brief GetColor
     * @return
     */
    PlayingField::OccupationState GetColor() const;

    /**
     * @brief SetName
     * @param name
     */
    void SetName(std::string name);

    /**
     * @brief GetSkill
     * @return
     */
    int GetSkill() const;

    /**
     * @brief SetSkill
     * @param skill
     */
    void SetSkill(int skill);



    static string Serialize(const Player p);

    static bool Deserialize(std::string str, Player *p);

private:
    const static char delimiter;


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
    unsigned int m_playerSkill;

};

#endif // PLAYER_H
