#include "Player.h"

const char Player::delimiter = ';';

Player::Player()
{
    this->m_playerType = HUMAN;
    this->m_playerName = "NAME";
    this->m_playerColor = PlayingField::NONE;
    this->m_playerSkill = -1;
}

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

Player *Player::Deserialize(std::string str) throw(DeserializationException)
{
    std::vector<string> elems;    
    split(str, delimiter, elems);

    Player *p = NULL;

    try
    {
        PlayerType pT = (PlayerType)stoi(elems.at(0));
        PlayingField::OccupationState pO = (PlayingField::OccupationState)stoi(elems.at(2));

        p = new Player(pT, elems.at(1), pO, stoi(elems.at(3)));
    }
    catch(std::invalid_argument)
    {
        Logger::GetLoggerIntance()->LogInfo(" Player::Deserialize invalid_argument (Player)", __FILE__, __LINE__);
        throw DESERIALIZATION_FAILED;
    }



    return p;
}

