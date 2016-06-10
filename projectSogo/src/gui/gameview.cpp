#include "./Gameview.h"

GameView::GameView(GameData *data, QWidget *parent)
    : QWidget(parent)
{
    m_mainLayout = new QVBoxLayout(this);

    QWidget *bottomView = new QWidget();
    m_mainLayout->addWidget(bottomView);

    this->bottomViewLayout = new QStackedLayout(bottomView);



    this->m_data = data;

    this->m_gameLoop = new GameManager(this->m_data);



    this->m_inputArea = new GameInputArea(this->m_gameLoop, this);

    bottomViewLayout->addWidget(m_inputArea);

    QuitButton = new QPushButton("End", this);

    QObject::connect(this->QuitButton, &QPushButton::clicked, this, &GameView::SwitchToEndGameButton);

    bottomViewLayout->addWidget(QuitButton);

    this->m_gameVis = new GameVisualizer(this->m_data, this);
    m_mainLayout->addWidget(this->m_gameVis);


    QObject::connect(this->m_gameLoop, &GameManager::AIWon, this, &GameView::EndGame);

    QObject::connect(this->m_gameLoop, &GameManager::AITurnFinished, this->m_inputArea->GetHistoryDisplay(), &HistoryDisplay::UpdateHistory);

    QObject::connect(this->m_gameLoop, &GameManager::AITurnFinished, this->m_gameVis, &GameVisualizer::UpdateView);

    QObject::connect(this->m_gameLoop, &GameManager::finished, this->m_gameLoop, &GameManager::deleteLater);

    this->m_gameLoop->start();



    QObject::connect(this->m_gameLoop, &GameManager::PlayerWon, this, &GameView::EndGame);

    QObject::connect(this->m_gameLoop, &GameManager::InputMade, this->m_inputArea->GetHistoryDisplay(), &HistoryDisplay::UpdateHistory);

    QObject::connect(this->m_gameLoop, &GameManager::InputMade, this->m_gameVis, &GameVisualizer::UpdateView);

    QObject::connect(this->m_inputArea->GetPlayerInputControls(), &PlayerInput::InputConfirmed, this->m_gameLoop, &GameManager::InputConfirmationDetected);

}

GameView::~GameView()
{
    delete(this->m_mainLayout);
    delete(this->m_data);
}

void GameView::SwitchToEndGameButton()
{
    this->GameEnded(*(this->m_data));
}


void GameView::EndGame()
{

    if(this->m_gameLoop != NULL)
    {
        this->m_gameLoop->Stop();
    }
    else
    {
        Logger::GetLoggerIntance()->LogInfo("gameLoop already null");
    }

    bottomViewLayout->setCurrentWidget(this->QuitButton);
    //emit GameEnded(*(this->m_data));
}
