#ifndef GAMEMANAGERTHREAD_H
#define GAMEMANAGERTHREAD_H

#include <QThread>
#include "GameData.h"
#include "AI.h"
#include "Player.h"

class AIGameLoop : public QThread
{
    Q_OBJECT
public:
    AIGameLoop(GameData *data);
    ~AIGameLoop();

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

    inline void Stop()
    {
        m_stop = true;
    }

signals:
    void AITurnFinished();
    void AIWon();

private:
    GameData *m_data;

    bool m_stop;

    void AILoop();
};




#endif // GAMEMANAGERTHREAD_H
