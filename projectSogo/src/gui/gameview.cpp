#include "./Gameview.h"

GameView::GameView(GameData *data, QWidget *parent)
    : QWidget(parent)
{
    m_mainLayout = new QVBoxLayout(this);

    this->m_data = data;


    QWidget *bottomView = new QWidget();
    m_mainLayout->addWidget(bottomView);

    this->bottomViewLayout = new QStackedLayout(bottomView);

    this->m_inputArea = new GameInputArea(this->m_data, this);

    bottomViewLayout->addWidget(m_inputArea);

    QuitButton = new QPushButton("End", this);

    QObject::connect(this->QuitButton, &QPushButton::clicked, this, &GameView::SwitchToEndGameButton);

    bottomViewLayout->addWidget(QuitButton);

    this->m_gameVis = new GameVisualizer(this->m_data, this);
    m_mainLayout->addWidget(this->m_gameVis);

    this->gameLoop = NULL;

    if(data->GetPlayer1()->GetType() == Player::Ai || data->GetPlayer2()->GetType() == Player::Ai)
    {
        this->gameLoop = new AIGameLoop(this->m_data);
        QObject::connect(this->gameLoop, &AIGameLoop::AIWon, this, &GameView::EndGame);

        QObject::connect(this->gameLoop, &AIGameLoop::AITurnFinished, this->m_inputArea->GetHistoryDisplay(), &HistoryDisplay::UpdateHistory);

        QObject::connect(this->gameLoop, &AIGameLoop::AITurnFinished, this->m_gameVis, &GameVisualizer::UpdateView);
        this->gameLoop->start();
        QObject::connect(this->gameLoop, &AIGameLoop::finished, this->gameLoop, &AIGameLoop::deleteLater);
    }


    QObject::connect(this->m_inputArea->GetPlayerInputControls(), &PlayerInput::PlayerWon, this, &GameView::EndGame);

    QObject::connect(this->m_inputArea->GetPlayerInputControls(), &PlayerInput::InputMade, this->m_inputArea->GetHistoryDisplay(), &HistoryDisplay::UpdateHistory);

    QObject::connect(this->m_inputArea->GetPlayerInputControls(), &PlayerInput::InputMade, this->m_gameVis, &GameVisualizer::UpdateView);

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

    if(this->gameLoop != NULL)
    {
        this->gameLoop->Stop();
    }
    else
    {
        Logger::GetLoggerIntance()->LogInfo("gameLoop already null");
    }

    bottomViewLayout->setCurrentWidget(this->QuitButton);
    //emit GameEnded(*(this->m_data));
}
