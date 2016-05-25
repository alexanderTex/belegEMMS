#ifndef GAMEDATA_H
#define GAMEDATA_H

#include <stdexcept>

#include "PlayingField.h"
#include "Vector2.h"
#include "Logger.h"
#include "../include/Subject.h"
#include "Player.h"


class GameData : public Subject
{
public:
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

    inline void SwitchPlayer()
    {
        m_currentPlayer = m_currentPlayer == player1 ? player2 : player1;
        this->NotifyAllObserver();
    }


    void MakeMove(Vector3 pos);

private:
    PlayingField *m_field;
    Player *m_currentPlayer;
    Player *player1;
    Player *player2;
};

#endif // GAMEDATA_H
