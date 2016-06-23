#include "./mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QWidget *main = new QWidget();

    m_allAroundLayout = new QVBoxLayout(main);

    QPushButton *changeLanguageButton = new QPushButton(tr("changeButton"), main);
    QObject::connect(changeLanguageButton, &QPushButton::clicked, this, &MainWindow::ChangeLanguage);
    m_allAroundLayout->addWidget(changeLanguageButton);


    QWidget *workspace = new QWidget();
    m_allAroundLayout->addWidget(workspace);

    // JUST FOR TESTING WOULD BE GIVEN FROM OUTSIDE
    Player *one = new Player(Player::Ai, "Dirk", PlayingField::Blue);
    Player *two = new Player(Player::Human, "Frank", PlayingField::Red);

    GameData *data = new GameData(new PlayingField(), one, two, one);

    m_layout = new QStackedLayout(workspace);

    this->m_gameView = new GameView( data, workspace);
    m_layout->addWidget(this->m_gameView);
    QObject::connect(this->m_gameView, &GameView::PauseMenu, this, &MainWindow::ShowPauseMenu);
    QObject::connect(this->m_gameView, &GameView::GameEnded, this, &MainWindow::QuitMainWindow);

    this->m_pauseMenu = new PauseMenu(workspace);
    m_layout->addWidget(this->m_pauseMenu);
    QObject::connect(this->m_pauseMenu, &PauseMenu::ResumeButtonPressed, this, &MainWindow::ShowGameView);

    setCentralWidget(main);
    show();

}


MainWindow::MainWindow(QTranslator *translator, QWidget *parent)
    : QMainWindow(parent)
{
    QWidget *main = new QWidget();

    m_allAroundLayout = new QVBoxLayout(main);

    QPushButton *changeLanguageButton = new QPushButton(tr("changeButton"), main);
    QObject::connect(changeLanguageButton, &QPushButton::clicked, this, &MainWindow::ChangeLanguage);
    m_allAroundLayout->addWidget(changeLanguageButton);


    QWidget *workspace = new QWidget();
    m_allAroundLayout->addWidget(workspace);

    // JUST FOR TESTING WOULD BE GIVEN FROM OUTSIDE
    Player *one = new Player(Player::Ai, "Dirk", PlayingField::Blue);
    Player *two = new Player(Player::Human, "Frank", PlayingField::Red);

    GameData *data = new GameData(new PlayingField(), one, two, one);

    m_layout = new QStackedLayout(workspace);

    this->m_gameView = new GameView( data, workspace);
    m_layout->addWidget(this->m_gameView);
    QObject::connect(this->m_gameView, &GameView::PauseMenu, this, &MainWindow::ShowPauseMenu);
    QObject::connect(this->m_gameView, &GameView::GameEnded, this, &MainWindow::QuitMainWindow);

    this->m_pauseMenu = new PauseMenu(workspace);
    m_layout->addWidget(this->m_pauseMenu);
    QObject::connect(this->m_pauseMenu, &PauseMenu::ResumeButtonPressed, this, &MainWindow::ShowGameView);

    setCentralWidget(main);
    show();


    this->m_translator = translator;
}

MainWindow::~MainWindow()
{
    delete(m_gameView);
    delete(m_pauseMenu);
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
