#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGridLayout>

#include "./Gameview.h"
#include "../include/core/PlayingField.h"
#include "../include/core/GameData.h"
#include "Player.h"
#include "GameManager.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    GameView *m_GameView;
    GameData *data;
    GameManager *manager;

};

#endif // MAINWINDOW_H
