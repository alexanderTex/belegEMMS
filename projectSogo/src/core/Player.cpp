#include "Player.h"

const char Player::delimiter = ';';

Player::Player(PlayerType type, std::string name, PlayingField::OccupationState color, unsigned int skill)
{
    this->m_playerType = type;
    this->m_playerName = name;
    this->m_playerColor = color;

    if(m_playerType == Player::AI)
    {
        if(skill < 1)
        {
            skill = 1;
        }
    }
    this->m_playerSkill = skill;
}

Player::Player(const Player &src)
{
    this->m_playerType = src.GetType();
    this->m_playerName = src.GetName();
    this->m_playerColor = src.GetColor();
    this->m_playerSkill = src.GetSkill();
}

Player::PlayerType Player::GetType() const
{
    return m_playerType;
}

/**
 * @brief GetName
 * @return
 */
std::string Player::GetName() const
{
    return m_playerName;
}

/**
 * @brief GetColor
 * @return
 */
PlayingField::OccupationState Player::GetColor() const
{
    return m_playerColor;
}

/**
 * @brief SetName
 * @param name
 */
void Player::SetName(std::string name)
{
    m_playerName = name;
}

/**
 * @brief GetSkill
 * @return
 */
int Player::GetSkill() const
{
    return m_playerSkill;
}

/**
 * @brief SetSkill
 * @param skill
 */
void Player::SetSkill(int skill)
{
    m_playerSkill = skill;
}


string Player::Serialize(const Player p)
{
    stringstream s;

    s << p.GetType() << delimiter << p.GetName() << delimiter << p.GetColor() << delimiter << p.GetSkill();

    return s.str();
}

bool Player::Deserialize(std::string str, Player *p)
{
    std::vector<string> elems;
    Logger::GetLoggerIntance()->LogInfo(" Player::Deserialize before split (Player)", __FILE__, __LINE__);
    split(str, delimiter, elems);

    bool worked = true;

    try
    {
        PlayerType pT = (PlayerType)stoi(elems.at(0));
        Logger::GetLoggerIntance()->LogInfo(" Player::Deserialize PlayerType Loaded (Player)", __FILE__, __LINE__);
        PlayingField::OccupationState pO = (PlayingField::OccupationState)stoi(elems.at(2));
        Logger::GetLoggerIntance()->LogInfo(" Player::Deserialize PlayerOccupationState Loaded (Player)", __FILE__, __LINE__);
        p = new Player(pT, elems.at(1), pO, stoi(elems.at(3)));
        Logger::GetLoggerIntance()->LogInfo(" Player::Deserialize Player created (Player)", __FILE__, __LINE__);
    }
    catch(std::invalid_argument)
    {
        Logger::GetLoggerIntance()->LogInfo(" Player::Deserialize invalid_argument (Player)", __FILE__, __LINE__);
        worked = false;
    }



    return worked;
}

