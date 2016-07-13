#ifndef GAMEVIEW_H
#define GAMEVIEW_H

#include <vector>

#include <QSound>

#include <QWidget>
#include <QEvent>

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGroupBox>

#include "../include/core/GameData.h"
#include "../include/core/Vector3.h"
#include "GameVisualizer.h"
#include "GameInputArea.h"

#include "GameManagerThread.h"

using namespace std;

/**
 * @brief The GameView class
 */
class GameView : public QWidget
{
    Q_OBJECT
public:
    explicit GameView( QWidget *parent = 0);
    GameView(GameData *data, QWidget *parent = 0);
    virtual ~GameView();

    inline GameVisualizer *GetVisualizer() const
    {
        return m_gameVis;
    }

    inline GameData *GetGameData() const
    {
        return m_data;
    }

    inline void InitGame(GameData *data)
    {
        Logger::GetLoggerIntance()->LogInfo("InitGame");
        *(this->m_data) = *data;
        this->m_gameVis->GameChanged();
        ShowGameInputView();
    }

    void StartGame();

    void PauseGame();

    inline void PlayAcceptSound()
    {
        QSound::play(":/sounds/Sounds/UI Beep Double Alternative (stereo).wav");
    }

    inline void PlayErrorSound()
    {
        QSound::play(":/sounds/Sounds/UI Error Double Note Down (stereo).wav");
    }

    inline void ShowGameInputView()
    {
        bottomViewLayout->setCurrentWidget(this->m_inputArea);
    }


    void ShowWinner();

    /**
     * @brief GameFinished
     * Called if a player won
     * to stop the gamelogic thread and
     * show leave button
     */
    void GameFinished();

    /**
     * @brief EndGame
     * called from leave button
     * calls GameEnded
     */
    void EndGame();

    inline void changeEvent(QEvent *event)
    {
        if (event->type() == QEvent::LanguageChange) {
            m_pauseMenuButton->setText(tr("Pausemenu"));

        } else
            QWidget::changeEvent(event);
    }


signals:
    /**
     * @brief GameEnded
     * Called when leave button pressed to go back to menu screen
     * @param data gamedata after game ended
     */
    void GameEnded(GameData *data);
    /**
     * @brief PauseMenu
     */
    void PauseMenu();


private:
    QStackedLayout *m_layoutSwitch;

    QWidget *m_pauseMenu;

    QVBoxLayout *m_mainLayout;

    QPushButton *m_pauseMenuButton;

    GameVisualizer *m_gameVis;

    QStackedLayout *bottomViewLayout;

    GameInputArea *m_inputArea;

    QWidget *endView;
    QVBoxLayout *endScreen;

    QLabel *WinLabel;
    QPushButton *QuitButton;


    GameData *m_data;

    GameManager *m_gameLoop;




};

#endif // GAMEVIEW_H
