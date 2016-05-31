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


class GameData : public Subject
{
public:
    enum GameDataException
    {
        PlayerNotInTheGame,
    };

    GameData(PlayingField *field, Player *p1, Player *p2, Player *startingPlayer);
    virtual ~GameData();


    inline const PlayingField *GetField() const
    {
        return m_field;
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

    inline void SwitchPlayer()
    {
        m_currentPlayer = m_currentPlayer == m_player1 ? m_player2 : m_player1;
        this->NotifyAllObserver();
    }

    void MakeMove(Vector3 pos) throw(PlayingField::FieldExeptions, std::out_of_range);


private:
    PlayingField *m_field;
    Player *m_currentPlayer;
    Player *m_player1;
    Player *m_player2;
    HistorySave *m_history;
};

#endif // GAMEDATA_H
