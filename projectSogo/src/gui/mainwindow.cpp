#include "./mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    Player *one = new Player(Player::Human, "Dirk", PlayingField::Blue);
    Player *two = new Player(Player::Ai, "Frank", PlayingField::Red);

    this->data = new GameData(new PlayingField(), one, two, one);
    manager = new GameManager(data);


    this->m_GameView = new GameView( this->data, this);
    this->data->AddListener(this->m_GameView->GetVisualizer());
    this->data->AddListener(this->manager);

    setCentralWidget(m_GameView);
    show();
}

MainWindow::~MainWindow()
{
    delete(m_GameView);
    delete(data);
    delete(manager);
}


