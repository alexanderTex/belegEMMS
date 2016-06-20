#include "./mainwindow.h"

MainWindow::MainWindow( QWidget *parent)
    : QMainWindow(parent)
{
    QWidget *main = new QWidget();

    // JUST FOR TESTING WOULD BE GIVEN FROM OUTSIDE
    Player *one = new Player(Player::Ai, "Dirk", PlayingField::Blue);
    Player *two = new Player(Player::Human, "Frank", PlayingField::Red);

    GameData *data = new GameData(new PlayingField(), one, two, one);

    m_layout = new QStackedLayout(main);

    this->m_gameView = new GameView( data, this);
    m_layout->addWidget(this->m_gameView);
    QObject::connect(this->m_gameView, &GameView::PauseMenu, this, &MainWindow::ShowPauseMenu);
    QObject::connect(this->m_gameView, &GameView::GameEnded, this, &MainWindow::QuitMainWindow);

    this->m_pauseMenu = new PauseMenu(this);
    m_layout->addWidget(this->m_pauseMenu);
    QObject::connect(this->m_pauseMenu, &PauseMenu::ResumeButtonPressed, this, &MainWindow::ShowGameView);

    setCentralWidget(main);
    show();
}

MainWindow::~MainWindow()
{
    delete(m_gameView);
}

void MainWindow::ShowGameView()
{
    m_layout->setCurrentWidget(this->m_gameView);
    m_gameView->StartGame();
}

void MainWindow::ShowPauseMenu()
{
    m_layout->setCurrentWidget(this->m_pauseMenu);
}
