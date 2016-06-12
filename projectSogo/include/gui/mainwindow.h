#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGridLayout>

#include "./GameView.h"
#include <QTextEdit>
#include "../include/core/PlayingField.h"
#include "../include/core/GameData.h"
#include "Player.h"

/**
 * @brief The MainWindow class
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    virtual ~MainWindow();

    inline GameView *GetGameView() const
    {
        return m_gameView;
    }

    /**
     * @brief ShowGameView
     */
    void ShowGameView();

    /**
     * @brief ShowPauseMenu
     */
    void ShowPauseMenu();

    /**
     * @brief ShowWinScreen
     * @param data
     */
    void ShowWinScreen(GameData *data);

private:
    QStackedLayout *m_layout;

    GameView *m_gameView;
    QPushButton *m_pauseMenu;
    QLabel *WinLabel;

};

#endif // MAINWINDOW_H
