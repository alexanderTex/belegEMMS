#include "../../include/core/GameData.h"

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
