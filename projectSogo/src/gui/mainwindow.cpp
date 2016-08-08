#include "./mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QWidget *main = new QWidget();


    m_allAroundLayout = new QVBoxLayout(main);

    m_changeLanguageButton = new QPushButton(tr("changeButton"), main);
    QObject::connect(m_changeLanguageButton, &QPushButton::clicked, this, &MainWindow::ChangeLanguage);
    m_allAroundLayout->addWidget(m_changeLanguageButton);


    QWidget *workspace = new QWidget();
    m_allAroundLayout->addWidget(workspace);

    // JUST FOR TESTING WOULD BE GIVEN FROM OUTSIDE
    Player *one = new Player(Player::AI, "Dirk", PlayingField::BLUE);
    Player *two = new Player(Player::HUMAN, "Frank", PlayingField::RED);

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

    m_changeLanguageButton = new QPushButton(tr("changeButton"), main);
    QObject::connect(m_changeLanguageButton , &QPushButton::clicked, this, &MainWindow::ChangeLanguage);
    m_allAroundLayout->addWidget(m_changeLanguageButton);


    QWidget *workspace = new QWidget();
    m_allAroundLayout->addWidget(workspace);

    // JUST FOR TESTING WOULD BE GIVEN FROM OUTSIDE
    Player *one = new Player(Player::AI, "Dirk", PlayingField::BLUE, 4);
    Player *two = new Player(Player::HUMAN, "Frank", PlayingField::RED);

    GameData *data = new GameData(new PlayingField(), one, two, one);

    m_layout = new QStackedLayout(workspace);

    // inout mainmenu
    this->m_startMenu = new StartMenu(workspace);
    m_layout->addWidget(m_startMenu);
    QObject::connect(m_startMenu, &StartMenu::switchToNewSession, this, &MainWindow::showNewSessionMenu);
    QObject::connect(m_startMenu, &StartMenu::switchToHighscore, this, &MainWindow::showHighscoreMenu);
    QObject::connect(m_startMenu, &StartMenu::quitGame, this, &MainWindow::QuitMainWindow);

    this->m_newSessionMenu = new NewSessionMenu(workspace);
    m_layout->addWidget(m_newSessionMenu);
    QObject::connect(m_newSessionMenu, &NewSessionMenu::showStartMenu, this, &MainWindow::showStartMenu);

    this->m_highscoreMenu = new HighscoreMenu(workspace);
    m_layout->addWidget(m_highscoreMenu);
    QObject::connect(m_highscoreMenu, &HighscoreMenu::showStartMenu, this, &MainWindow::showStartMenu);

    this->m_gameView = new GameView( data, workspace);
    m_layout->addWidget(this->m_gameView);
    QObject::connect(this->m_gameView, &GameView::PauseMenu, this, &MainWindow::ShowPauseMenu);

    QObject::connect(this->m_gameView, &GameView::GameEnded, this, &MainWindow::showStartMenu);

    this->m_pauseMenu = new PauseMenu(workspace);
    m_layout->addWidget(this->m_pauseMenu);
    QObject::connect(this->m_pauseMenu, &PauseMenu::ResumeButtonPressed, this, &MainWindow::ShowGameView);
    QObject::connect(this->m_pauseMenu, &PauseMenu::QuitGameButtonPressed, this->m_gameView, &GameView::EndGame);
    QObject::connect(this->m_pauseMenu, &PauseMenu::QuitGameButtonPressed, this, &MainWindow::showStartMenu);

    // catch startGame from NewSession to start a new Game
    QObject::connect(this->m_newSessionMenu, &NewSessionMenu::startGame, this, &MainWindow::startNewGame);
    //QObject::connect(this->m_newSessionMenu, &NewSessionMenu::startGame, this, &MainWindow::ShowGameView);

    setCentralWidget(main);
    show();


    this->m_translator = translator;
}

MainWindow::~MainWindow()
{
    delete(m_gameView);
    delete(m_pauseMenu);
}

void MainWindow::startNewGame()
{
    this->m_newSessionMenu->mergeGameData();
    this->m_gameView->InitGame(this->m_newSessionMenu->m_gameData);
    this->ShowGameView();
}

void MainWindow::ShowGameView()
{
    m_layout->setCurrentWidget(this->m_gameView);
    m_gameView->StartGame();
}

void MainWindow::showNewSessionMenu()
{
    m_layout->setCurrentWidget(this->m_newSessionMenu);
}

void MainWindow::showHighscoreMenu()
{
    m_layout->setCurrentWidget(this->m_highscoreMenu);
}

void MainWindow::showStartMenu()
{
    m_layout->setCurrentWidget(this->m_startMenu);
}

void MainWindow::ShowPauseMenu()
{
    m_layout->setCurrentWidget(this->m_pauseMenu);
}

void MainWindow::ChangeLanguage()
{
    qApp->removeTranslator(m_translator);

    delete(m_translator);

    m_translator = new QTranslator();

    if(m_languageEnglish)
    {
        if(m_translator->load(":/sprache/Translations/sogoapp_de.qm"))
        {
            std::cout << "translator loaded" << std::endl;
        }
        else
        {
            std::cout << "translator did not load...whyever!!!" << std::endl;
        }
        m_languageEnglish = false;
    }
    else
    {
        if(m_translator->load(":/sprache/Translations/sogoapp_en.qm"))
        {
            std::cout << "translator loaded" << std::endl;
        }
        else
        {
            std::cout << "translator did not load...whyever!!!" << std::endl;
        }
        m_languageEnglish = true;
    }
    // qm datei muss in Ressource ordner sein um geladen werden

    qApp->installTranslator(m_translator);

}
