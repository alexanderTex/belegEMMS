#include "./Gameview.h"

GameView::GameView(GameData *data, QWidget *parent)
    : QWidget(parent)
{
    m_mainLayout = new QVBoxLayout(this);

    this->m_data = data;

    Logger::GetLoggerIntance()->LogInfo("Stuff");


    this->m_inputArea = new GameInputArea(this->m_data, this);
    m_mainLayout->addWidget(this->m_inputArea);


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
    }

    Logger::GetLoggerIntance()->LogInfo("Stuff2");



    QObject::connect(this->m_inputArea->GetPlayerInputControls(), &PlayerInput::PlayerWon, this, &GameView::EndGame);

    QObject::connect(this->m_inputArea->GetPlayerInputControls(), &PlayerInput::InputMade, this->m_inputArea->GetHistoryDisplay(), &HistoryDisplay::UpdateHistory);

    QObject::connect(this->m_inputArea->GetPlayerInputControls(), &PlayerInput::InputMade, this->m_gameVis, &GameVisualizer::UpdateView);

}

GameView::~GameView()
{
    Logger::GetLoggerIntance()->LogInfo("GameView Destructor");

    delete(this->m_mainLayout);
    Logger::GetLoggerIntance()->LogInfo("m_mainLayout deleted");

    Logger::GetLoggerIntance()->LogInfo("Stopping gameLoop");
    if(this->gameLoop != NULL)
    {
        this->gameLoop->Stop();
        Logger::GetLoggerIntance()->LogInfo("gameLoop stopped");
    }
    else
    {
        Logger::GetLoggerIntance()->LogInfo("gameLoop already null");
    }

    Logger::GetLoggerIntance()->LogInfo("GameView Destructor");

    Logger::GetLoggerIntance()->LogInfo("Deleting m_data");
    delete(this->m_data);
    Logger::GetLoggerIntance()->LogInfo("m_data deleted");
}

void GameView::EndGame()
{

    if(this->gameLoop != NULL)
    {
        Logger::GetLoggerIntance()->LogInfo("Before gameloop stop");
        this->gameLoop->Stop();
        Logger::GetLoggerIntance()->LogInfo("After gameloop stop");
    }

    Logger::GetLoggerIntance()->LogInfo("Before GameEnded Event");
    Logger::GetLoggerIntance()->LogInfo(this->m_data->GetPlayer1()->GetName());
    NotifyAllObserver();
    std::cout << "FUCK THIS SHIT!" << std::endl;
    Logger::GetLoggerIntance()->LogInfo("After GameEnded Event");
}
