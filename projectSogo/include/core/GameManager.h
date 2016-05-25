#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include "GameData.h"
#include "AI.h"

class GameManager : public IObserver
{
public:
    GameManager(GameData *data){m_data = data;}

void ComputeTurn();

inline void Notify()
{
    ComputeTurn();
}

private:
    GameData *m_data;
};

#endif // GAMEMANAGER_H
