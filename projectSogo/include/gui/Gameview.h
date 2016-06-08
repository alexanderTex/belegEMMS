#ifndef GAMEVIEW_H
#define GAMEVIEW_H

#include <vector>


#include <QWidget>

#include <QVBoxLayout>
#include <QHBoxLayout>

#include "../include/core/GameData.h"
#include "../include/core/Vector3.h"
#include "Gamevisualizer.h"
#include "Gameinputarea.h"

#include "GameManagerThread.h"

using namespace std;

class GameView : public QWidget, public Subject
{
    Q_OBJECT
public:
    explicit GameView(GameData *data, QWidget *parent = 0);
    virtual ~GameView();

    inline GameVisualizer *GetVisualizer() const
    {
        return m_gameVis;
    }

    inline GameData *GetGameData() const
    {
        return m_data;
    }

    void EndGame();


signals:
    void GameEnded(GameData data);

private:
    QVBoxLayout *m_mainLayout;

    GameVisualizer *m_gameVis;

    GameInputArea *m_inputArea;

    GameData *m_data;

    AIGameLoop *gameLoop;


};

#endif // GAMEVIEW_H
