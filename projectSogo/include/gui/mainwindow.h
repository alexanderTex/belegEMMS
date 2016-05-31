#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGridLayout>

#include "./Gameview.h"
#include <QTextEdit>
#include "../include/core/PlayingField.h"
#include "../include/core/GameData.h"
#include "Player.h"
#include <thread>
#include "GameManagerThread.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

    inline GameView *GetGameView() const
    {
        return m_gameView;
    }

private:
    GameView *m_gameView;
    std::thread *gameLoop;
};

#endif // MAINWINDOW_H
