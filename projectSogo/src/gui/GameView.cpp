#include "./GameView.h"

GameView::GameView(QWidget *parent)
    : QWidget(parent)
{
    this->m_data = new GameData();

    this->m_gameLoop = new GameManager();
    this->m_gameLoop->PauseGame();
    QObject::connect(this->m_gameLoop, &GameManager::finished, this->m_gameLoop, &GameManager::deleteLater);

    m_mainLayout = new QVBoxLayout(this);

    m_pauseMenuButton = new QPushButton(tr("Pausemenu"), this);
    m_mainLayout->addWidget(this->m_pauseMenuButton);
    QObject::connect(this->m_pauseMenuButton, &QPushButton::clicked, this, &GameView::PauseGame);

    this->m_gameVis = new GameVisualizer(this->m_gameLoop, this);
    m_mainLayout->addWidget(m_gameVis);

    QGroupBox *bottomView = new QGroupBox(this);
    this->bottomViewLayout = new QStackedLayout(bottomView);
    m_mainLayout->addWidget(bottomView);

    this->m_inputArea = new GameInputArea(this->m_gameLoop, bottomView);
    bottomViewLayout->addWidget(m_inputArea);

    endView = new QWidget(this);
    bottomViewLayout->addWidget(endView);
    endScreen = new QVBoxLayout(endView);

    this->WinLabel = new QLabel(endView);
    endScreen->addWidget(this->WinLabel);

    QuitButton = new QPushButton(tr("End"), endView);
    QObject::connect(this->QuitButton, &QPushButton::clicked, this, &GameView::EndGame);
    endScreen->addWidget(QuitButton);


    QObject::connect(this->m_gameLoop, &GameManager::PlayerWon, this, &GameView::GameFinished);

    QObject::connect(this->m_gameLoop, &GameManager::TurnFinished, this->m_inputArea->GetHistoryDisplay(), &HistoryDisplay::RedrawHistory);

    QObject::connect(this->m_gameLoop, &GameManager::TurnFinished, this->m_gameVis, &GameVisualizer::UpdateView);



    QObject::connect(this->m_gameLoop, &GameManager::PlayerWon, this, &GameView::GameFinished);

    QObject::connect(this->m_gameLoop, &GameManager::TurnFinished, this->m_inputArea->GetHistoryDisplay(), &HistoryDisplay::RedrawHistory);

    QObject::connect(this->m_gameLoop, &GameManager::TurnFinished, this->m_gameVis, &GameVisualizer::UpdateView);

    QObject::connect(this->m_inputArea->GetPlayerInputControls(), &PlayerInput::InputConfirmed, this->m_gameLoop, &GameManager::InputConfirmationDetected);

    // Sound Connects
    QObject::connect(this->m_gameLoop, &GameManager::PlayInputAcceptSound, this, &GameView::PlayAcceptSound);
    QObject::connect(this->m_gameLoop, &GameManager::PlayInputErrorSound, this, &GameView::PlayErrorSound);

}

GameView::GameView(GameData *data, QWidget *parent)
    : QWidget(parent)
{
    this->m_data = data;

    this->m_gameLoop = new GameManager(this->m_data);
    QObject::connect(this->m_gameLoop, &GameManager::finished, this->m_gameLoop, &GameManager::deleteLater);

    m_mainLayout = new QVBoxLayout(this);

    m_pauseMenuButton = new QPushButton(tr("Pausemenu"), this);
    m_mainLayout->addWidget(this->m_pauseMenuButton);
    QObject::connect(this->m_pauseMenuButton, &QPushButton::clicked, this, &GameView::PauseGame);



    this->m_gameVis = new GameVisualizer(this->m_gameLoop, this);
    m_mainLayout->addWidget(m_gameVis);

    QGroupBox *bottomView = new QGroupBox(this);
    this->bottomViewLayout = new QStackedLayout(bottomView);
    m_mainLayout->addWidget(bottomView);

    this->m_inputArea = new GameInputArea(this->m_gameLoop, bottomView);
    bottomViewLayout->addWidget(m_inputArea);

    endView = new QWidget(this);
    bottomViewLayout->addWidget(endView);
    endScreen = new QVBoxLayout(endView);

    this->WinLabel = new QLabel(endView);
    endScreen->addWidget(this->WinLabel);

    QuitButton = new QPushButton(tr("End"), endView);
    QObject::connect(this->QuitButton, &QPushButton::clicked, this, &GameView::EndGame);
    endScreen->addWidget(QuitButton);


    QObject::connect(this->m_gameLoop, &GameManager::PlayerWon, this, &GameView::GameFinished);

    QObject::connect(this->m_gameLoop, &GameManager::TurnFinished, this->m_inputArea->GetHistoryDisplay(), &HistoryDisplay::RedrawHistory);

    QObject::connect(this->m_gameLoop, &GameManager::TurnFinished, this->m_gameVis, &GameVisualizer::UpdateView);



    QObject::connect(this->m_gameLoop, &GameManager::PlayerWon, this, &GameView::GameFinished);

    QObject::connect(this->m_gameLoop, &GameManager::TurnFinished, this->m_inputArea->GetHistoryDisplay(), &HistoryDisplay::RedrawHistory);

    QObject::connect(this->m_gameLoop, &GameManager::TurnFinished, this->m_gameVis, &GameVisualizer::UpdateView);

    QObject::connect(this->m_inputArea->GetPlayerInputControls(), &PlayerInput::InputConfirmed, this->m_gameLoop, &GameManager::InputConfirmationDetected);



    // Sound Connects
    QObject::connect(this->m_gameLoop, &GameManager::PlayInputAcceptSound, this, &GameView::PlayAcceptSound);
    QObject::connect(this->m_gameLoop, &GameManager::PlayInputErrorSound, this, &GameView::PlayErrorSound);
}

GameView::~GameView()
{
    delete(this->m_mainLayout);
}

void GameView::StartGame()
{
    this->m_gameLoop->StartGame();
}

void GameView::PauseGame()
{
    this->m_gameLoop->PauseGame();
    PauseMenu();
}

void GameView::EndGame()
{
    this->m_gameLoop->SuspendProcessingLoop();
    emit GameEnded(this->m_data);
}


void GameView::GameFinished()
{
    // Play WinSound

    FillInWinner();
    bottomViewLayout->setCurrentWidget(this->endView);

}

void GameView::FillInWinner()
{
    stringstream s;

    s << "The winner is : " << this->m_data->GetCurrentPlayer()->GetName().c_str() << "! YEAH!";

    this->WinLabel->setText(QString(s.str().c_str()));

    this->bottomViewLayout->setCurrentWidget(this->endView);

    Logger::GetLoggerIntance()->LogInfo(s.str());
}
