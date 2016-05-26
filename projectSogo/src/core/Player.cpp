#include "Player.h"

Player::Player(PlayerType type, std::string name, PlayingField::OccupationState color)
{
    this->m_type = type;
    this->m_playerName = name;
    this->m_playerColor = color;
}
