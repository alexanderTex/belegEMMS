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

    inline std::vector<Player*> *GetPlayers() const
    {
        return new std::vector<Player*>();
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

    inline Vector3  GetLastMove() const
    {
        return m_history->GetLastMove()->position;
    }

    inline const Player * GetOpponent(const Player *p) const throw(GameDataException)
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

    inline void OccupySlot(int x, int y, int z, PlayingField::OccupationState playerColor) throw(out_of_range, PlayingField::FieldExeptions)
    {
        this->m_field->OccupySlot(x, y, z, playerColor);
        Vector3 pos(x,y,z);
        this->m_history->AddMove(pos, *(this->GetCurrentPlayer()));
    }


    inline void SwitchPlayer()
    {
        m_currentPlayer = m_currentPlayer == m_player1 ? m_player2 : m_player1;        
    }




private:
    PlayingField *m_field;
    Player *m_currentPlayer;
    Player *m_player1;
    Player *m_player2;
    HistorySave *m_history;
};

#endif // GAMEDATA_H
