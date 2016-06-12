#include "./mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QWidget *main = new QWidget();

    // JUST FOR TESTING WOULD BE GIVEN FROM OUTSIDE
    Player *one = new Player(Player::Ai, "Dirk", PlayingField::Blue);
    Player *two = new Player(Player::Ai, "Frank", PlayingField::Red);

    GameData *data = new GameData(new PlayingField(), one, two, one);

    m_layout = new QStackedLayout(main);

    this->m_gameView = new GameView( data, this);
    m_layout->addWidget(this->m_gameView);
    QObject::connect(this->m_gameView, &GameView::PauseMenu, this, &MainWindow::ShowPauseMenu);
    QObject::connect(this->m_gameView, &GameView::GameEnded, this, &MainWindow::ShowWinScreen);

    this->WinLabel = new QLabel(this);
    m_layout->addWidget(this->WinLabel);

    this->m_pauseMenu = new QPushButton(tr("Resume"), this);
    m_layout->addWidget(this->m_pauseMenu);
    QObject::connect(this->m_pauseMenu, &QPushButton::clicked, this, &MainWindow::ShowGameView);

    setCentralWidget(main);
    show();
}

MainWindow::~MainWindow()
{
    delete(m_gameView);
    delete(WinLabel);
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

void MainWindow::ShowWinScreen(GameData *data)
{
    stringstream s;

    s << "The winner is : " << data->GetCurrentPlayer()->GetName().c_str() << "! YEAH!";

    WinLabel->setText(QString(s.str().c_str()));

    m_layout->setCurrentWidget(WinLabel);

    Logger::GetLoggerIntance()->LogInfo(s.str());

    delete(data);
}

