#include "../../include/core/GameData.h"

const char GameData::delimiter = '|';

GameData::GameData()
{
    this->m_field = NULL;
    this->m_player1 = NULL;
    this->m_player2 = NULL;
    this->m_currentPlayer = NULL;
    this->m_history = new HistorySave();
}

GameData::GameData(PlayingField *field, Player *p1, Player *p2, Player *startingPlayer)
{
    this->m_field = field;
    this->m_player1 = p1;
    this->m_player2 = p2;
    this->m_currentPlayer = startingPlayer;
    this->m_history = new HistorySave();
}

GameData::GameData(const GameData &src)
{
    this->m_field = new PlayingField(*(src.GetField()));
    this->m_history = new HistorySave(*(src.GetHistory()));
    this->m_player1 = new Player(*(src.GetPlayer1()));
    this->m_player2 = new Player(*(src.GetPlayer2()));
    this->m_currentPlayer = src.GetCurrentPlayer()->GetColor() == this->m_player1->GetColor() ? this->m_player1 : this->m_player2;
}

GameData::GameData(PlayingField *field, Player *p1, Player *p2, Player *startingPlayer, HistorySave *historySave)
    :   GameData(field, p1, p2, startingPlayer)
{
    this->m_history = historySave;
}

GameData::~GameData()
{
    delete(m_field);
    delete(m_player1);
    delete(m_player2);
    delete(m_history);
}

/**
 * @brief GetField
 * @return
 */
const PlayingField *GameData::GetField() const
{
    return m_field;
}

/**
 * @brief GetPlayers
 * @return
 */
std::vector<const Player*> *GameData::GetPlayers() const
{
    std::vector<const Player*> *ret = new std::vector<const Player*>();
    ret->push_back(m_player1);
    ret->push_back(m_player2);
    return ret;
}

/**
 * @brief GetPlayer1
 * @return
 */
Player *GameData::GetPlayer1() const
{
    return m_player1;
}

/**
 * @brief GetPlayer2
 * @return
 */
Player *GameData::GetPlayer2() const
{
    return m_player2;
}

/**
 * @brief GetCurrentPlayer
 * @return
 */
Player *GameData::GetCurrentPlayer() const
{
    return m_currentPlayer;
}

/**
 * @brief GetLastMove
 * @return
 */
Vector3 GameData::GetLastMove() const
{
    return *(m_history->GetLastMove()->position);
}

/**
 * @brief GetOpponent
 * @param p
 * @return
 * throws GamedataException if the given player p is not part of the game
 */
const Player *GameData::GetOpponent(const Player *p) const throw(GameDataException)
{
    if(p == m_player1)
    {
        return m_player2;
    }
    else if(p == m_player2)
    {
        return m_player1;
    }
    else
    {
        throw(PlayerNotInTheGame);
    }
}

/**
 * @brief GetHistory
 * @return
 */
const HistorySave *GameData::GetHistory() const
{
    return m_history;
}

/**
 * @brief OccupySlot
 * occupies slotint playingfield and adds the move to the move history
 * @param x horizontal coordinate
 * @param y vertical coordinate
 * @param z depth coordinate
 * @param playerColor
 * throws out_of_range if the x,y or z is out of the range of the playingfield
 * throws FieldException if occupying the slot in Playingfield failed
 */
void GameData::OccupySlot(int x, int y, int z, PlayingField::OccupationState playerColor) throw(out_of_range, PlayingField::FieldExeptions)
{
    this->m_field->OccupySlot(x, y, z, playerColor);
    Vector3 pos(x,y,z);
    this->m_history->AddMove(pos, *(this->GetCurrentPlayer()));
}

/**
 * @brief SwitchPlayer
 * switch currentplayer to other player
 */
void GameData::SwitchPlayer()
{
    m_currentPlayer = m_currentPlayer == m_player1 ? m_player2 : m_player1;
}

string GameData::Serialize(const GameData& data)
{
    stringstream s;

    int current = 0;
    if(data.GetCurrentPlayer() == data.GetPlayer1())
    {
        current = 1;
    }
    else
    {
        current = 2;
    }

    s << PlayingField::Serialize(*data.GetField()) << delimiter << Player::Serialize(*data.GetPlayer1()) << delimiter << Player::Serialize(*data.GetPlayer2())
      << delimiter << current << delimiter << HistorySave::Serialize(*data.GetHistory());


    return s.str();
}

bool GameData::Deserialize(std::string str, GameData *data)
{
    std::vector<string> elems;

    split(str, delimiter, elems);

    bool worked = true;

    // 1. PlayingField
    PlayingField *field;
    if(!PlayingField::Deserialize(elems.at(0), field) || field == NULL)
    {
        worked = false;
    }

    // 2. Player 1
    Player *p1;

    if(!Player::Deserialize(elems.at(1), p1) || p1 == NULL)
    {
        worked = false;
    }
    // 3. Player 2
    Player *p2;
    if(!Player::Deserialize(elems.at(2), p2) || p2 == NULL)
    {
        worked = false;
    }
    // 4. integer currentPlayer
    int current = 0;
    try
    {
        current = stoi(elems.at(3));
    }
    catch(std::invalid_argument)
    {
        worked = false;
    }

    // 5. History
    HistorySave *history;
    if(!HistorySave::Deserialize(elems.at(3), history) || history == NULL)
    {
        worked = false;
    }

    Player *currentPlayer;
    if(current == 1)
    {
        currentPlayer = p1;
    }
    else if(current == 2)
    {
        currentPlayer = p2;
    }
    else
    {
        worked = false;
    }

    if(worked)
        data = new GameData(field, p1, p2, currentPlayer, history);

    return worked;

}

