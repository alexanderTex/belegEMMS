#ifndef GAMEVIEW_H
#define GAMEVIEW_H

#include <vector>


#include <QWidget>
#include <QEvent>

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGroupBox>

#include "../include/core/GameData.h"
#include "../include/core/Vector3.h"
#include "Gamevisualizer.h"
#include "GameInputArea.h"

#include "GameManagerThread.h"

using namespace std;

class GameView : public QWidget
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

    void SwitchToEndGameButton();


signals:
    void GameEnded(GameData &data);
    void GameQuit(GameData &data);
    void PauseMenu();


private:
    QVBoxLayout *m_mainLayout;

    GameVisualizer *m_gameVis;

    QStackedLayout *bottomViewLayout;

    GameInputArea *m_inputArea;

    QPushButton *QuitButton;

    GameData *m_data;

    GameManager *m_gameLoop;


};

#endif // GAMEVIEW_H
