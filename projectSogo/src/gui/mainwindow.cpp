#include "./mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{

    // JUST FOR TESTING WOULD BE GIVEN FROM OUTSIDE
    Player *one = new Player(Player::Human, "Dirk", PlayingField::Blue);
    Player *two = new Player(Player::Ai, "Frank", PlayingField::Red);

    GameData *data = new GameData(new PlayingField(), one, two, one);

    QWidget *main = new QWidget(this);

    this->m_gameView = new GameView( data, main);
    gameLoop = new std::thread(AILoop, two, data);
    gameLoop->detach();

    setCentralWidget(m_gameView);
    show();
}

MainWindow::~MainWindow()
{
    delete(m_gameView);
    delete(gameLoop);
}


