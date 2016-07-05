#include "Player.h"

Player::Player(PlayerType type, std::string name, PlayingField::OccupationState color, int skill)
{
    this->m_playerType = type;
    this->m_playerName = name;
    this->m_playerColor = color;
    this->m_playerSkill = skill;
}

Player::Player(const Player &src)
{
    this->m_playerType = src.GetType();
    this->m_playerName = src.GetName();
    this->m_playerColor = src.GetColor();
    this->m_playerSkill = src.GetSkill();
}
