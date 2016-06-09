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


class GameData
{
public:
    enum GameDataException
    {
        PlayerNotInTheGame,
    };

    GameData(PlayingField *field, Player *p1, Player *p2, Player *startingPlayer);

    // constructor with historysave*

    GameData(const GameData *src);

    virtual ~GameData();


    inline const PlayingField *GetField() const
    {
        return m_field;
    }

    inline Player *GetPlayer1() const
    {
        return m_player1;
    }

    inline Player *GetPlayer2() const
    {
        return m_player2;
    }

    inline const Player *GetCurrentPlayer() const
    {
        return m_currentPlayer;
    }

    inline  Vector3 *const GetLastMove() const
    {
        return m_history->GetLastMove()->position;
    }

    inline  Player *const GetOpponent(const Player *p) const throw(GameDataException)
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

    inline const HistorySave *GetHistory() const
    {
        return m_history;
    }

    inline void SwitchPlayer()
    {
        m_currentPlayer = m_currentPlayer == m_player1 ? m_player2 : m_player1;        
    }

    /**
     * @brief Tries to Occupy the given position , adds the move to the history, checks if the player won ( return true if won),
     * switches currentplayer, and sends out event that a move is done
     * @param pos
     * @return true if the player just won the game
     */
    bool MakeMove(Vector3 pos) throw(PlayingField::FieldExeptions, std::out_of_range);


private:
    PlayingField *m_field;
    Player *m_currentPlayer;
    Player *m_player1;
    Player *m_player2;
    HistorySave *m_history;
};

#endif // GAMEDATA_H
