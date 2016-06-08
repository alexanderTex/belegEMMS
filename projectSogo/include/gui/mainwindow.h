#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGridLayout>

#include "./Gameview.h"
#include <QTextEdit>
#include "../include/core/PlayingField.h"
#include "../include/core/GameData.h"
#include "Player.h"

class MainWindow : public QMainWindow, public IObserver
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    virtual ~MainWindow();

    inline GameView *GetGameView() const
    {
        return m_gameView;
    }

    inline void Notify()
    {
        ShowWinScreen(*(this->m_gameView->GetGameData()));
    }

    void ShowWinScreen(GameData data);

private:
    QStackedLayout *m_layout;

    GameView *m_gameView;
    QLabel *WinLabel;

};

#endif // MAINWINDOW_H
