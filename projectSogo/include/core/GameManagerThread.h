#ifndef GAMEMANAGERTHREAD_H
#define GAMEMANAGERTHREAD_H

#include <QThread>
#include "GameData.h"
#include "AI.h"
#include "Player.h"

class GameManager : public QThread
{
    Q_OBJECT
public:
    GameManager(GameData *data);
    ~GameManager();

    virtual void run();

    struct AI
    {
        AI(Player *player, bool hasMove = false)
        {
            this->player = player;
            this->hasMove = hasMove;
        }

        Player *player;
        bool hasMove;
    };

    inline const GameData* GetGameData() const
    {
        return this->m_data;
    }

    inline void Stop()
    {
        m_stop = true;
    }

    inline void InputConfirmationDetected(Vector2 pos)
    {
        playerPosChoice = pos;
        m_playerInputConfirmed = true;
    }

    /**
     * @brief Tries to Occupy the given position , adds the move to the history, checks if the player won ( return true if won),
     * switches currentplayer, and sends out event that a move is done
     * @param pos
     * @return true if the player just won the game
     */
    bool MakeMove(Vector3 pos) throw(PlayingField::FieldExeptions, std::out_of_range);   

signals:
    void InputMade();
    void PlayerWon();
    void AITurnFinished();
    void AIWon();

private:
    Vector2 playerPosChoice;

    GameData *m_data;

    bool m_stop;

    bool m_playerInputConfirmed;

    void AILoop();
};




#endif // GAMEMANAGERTHREAD_H
