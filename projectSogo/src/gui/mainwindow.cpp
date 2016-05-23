#include "./mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->data = new GameData(new PlayingField(), PlayingField::Blue);
    this->m_GameView = new GameView( this->data, this);
    this->data->AddListener(this->m_GameView->GetVisualizer());

    setCentralWidget(m_GameView);
    show();
}

MainWindow::~MainWindow()
{

}


