#ifndef GAMEDATA_H
#define GAMEDATA_H

#include <stdexcept>

#include "PlayingField.h"
#include "Vector2.h"
#include "Logger.h"
#include "../include/Subject.h"
#include "Player.h"
#include "AI.h"
#include "HistorySave.h"

/**
 * @brief The GameData class
 * Holds a reference to the PlayingField
 * to both players and which one is the currentplayer
 */
class GameData
{
public:
    /**
     * @brief The GameDataException enum
     * thrown PlayerNotInTheGame when the player is not a player of the game
     */
    enum GameDataException
    {
        PlayerNotInTheGame,
    };

    /**
     * @brief GameData Default Constructor
    */
    GameData();

    /**
     * @brief GameData Initializes a Gamedata object with a given PlayingField
     * both players and the designated starting player
     * @param field given PlayingField
     * @param p1 player1
     * @param p2 player2
     * @param startingPlayer the beginning player
     */
    GameData(PlayingField *field, Player *p1, Player *p2, Player *startingPlayer);

    // constructor with historysave*
    /**
     * @brief GameData Copy Constructor
     * @param src Gamedata to copy from
     */
    GameData(const GameData &src);

    /**
     * @brief ~GameData
     */
    virtual ~GameData();

    /**
     * @brief GetField
     * @return
     */
    inline const PlayingField *GetField() const
    {
        return m_field;
    }

    /**
     * @brief GetPlayers
     * @return
     */
    inline std::vector<const Player*> *GetPlayers() const
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
    inline Player *GetPlayer1() const
    {
        return m_player1;
    }

    /**
     * @brief GetPlayer2
     * @return
     */
    inline Player *GetPlayer2() const
    {
        return m_player2;
    }

    /**
     * @brief GetCurrentPlayer
     * @return
     */
    inline Player *GetCurrentPlayer() const
    {
        return m_currentPlayer;
    }

    /**
     * @brief GetLastMove
     * @return
     */
    inline Vector3 GetLastMove() const
    {
        return *(m_history->GetLastMove()->position);
    }

    /**
     * @brief GetOpponent
     * @param p
     * @return
     * throws GamedataException if the given player p is not part of the game
     */
    inline const Player *GetOpponent(const Player *p) const throw(GameDataException)
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
    inline const HistorySave *GetHistory() const
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
    inline void OccupySlot(int x, int y, int z, PlayingField::OccupationState playerColor) throw(out_of_range, PlayingField::FieldExeptions)
    {
        this->m_field->OccupySlot(x, y, z, playerColor);
        Vector3 pos(x,y,z);
        this->m_history->AddMove(pos, *(this->GetCurrentPlayer()));
    }

    /**
     * @brief SwitchPlayer
     * switch currentplayer to other player
     */
    inline void SwitchPlayer()
    {
        m_currentPlayer = m_currentPlayer == m_player1 ? m_player2 : m_player1;        
    }




private:
    /**
     * @brief m_field
     */
    PlayingField *m_field;
    /**
     * @brief m_player1
     */
    Player *m_player1;
    /**
     * @brief m_player2
     */
    Player *m_player2;
    /**
     * @brief m_currentPlayer
     */
    Player *m_currentPlayer;
    /**
     * @brief m_history
     */
    HistorySave *m_history;
};

#endif // GAMEDATA_H
