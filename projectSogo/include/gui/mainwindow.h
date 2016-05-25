#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGridLayout>

#include "./Gameview.h"
#include "../include/core/PlayingField.h"
#include "../include/core/GameData.h"
#include "Player.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    GameView *m_GameView;

};

#endif // MAINWINDOW_H
