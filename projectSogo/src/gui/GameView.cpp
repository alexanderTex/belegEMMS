#include "./GameView.h"

const string GameView::SAVEFILENAME = "SaveGame.txt";
const string GameView::HIGHSCOREFILENAME = "HighScore.txt";


GameView::GameView(QWidget *parent)
    : QWidget(parent)
{
    this->m_data = new GameData();

    this->m_gameLoop = new GameManager();
    this->m_gameLoop->PauseGame();
    QObject::connect(this->m_gameLoop, &GameManager::finished, this->m_gameLoop, &GameManager::deleteLater);
    QObject::connect(qApp, &QCoreApplication::aboutToQuit, this->m_gameLoop, &GameManager::deleteLater);

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

    QObject::connect(this->m_gameLoop, &GameManager::TurnFinished, this->m_gameVis, &GameVisualizer::UpdateViews);



    QObject::connect(this->m_gameLoop, &GameManager::PlayerWon, this, &GameView::GameFinished);

    QObject::connect(this->m_gameLoop, &GameManager::TurnFinished, this->m_inputArea->GetHistoryDisplay(), &HistoryDisplay::RedrawHistory);

    QObject::connect(this->m_gameLoop, &GameManager::TurnFinished, this->m_gameVis, &GameVisualizer::UpdateViews);

    // Input
    QObject::connect(this->m_inputArea->GetPlayerInputControls(), &PlayerInput::InputConfirmed, this->m_gameLoop, &GameManager::InputConfirmationDetected);
    QObject::connect(this->m_gameVis, &GameVisualizer::InputDetected, this->m_gameLoop, &GameManager::InputConfirmationDetected);

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
    QObject::connect(qApp, &QCoreApplication::aboutToQuit, this->m_gameLoop, &GameManager::StopGameManagerThread);

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

    QObject::connect(this->m_gameLoop, &GameManager::TurnFinished, this->m_gameVis, &GameVisualizer::UpdateViews);



    QObject::connect(this->m_gameLoop, &GameManager::PlayerWon, this, &GameView::GameFinished);

    QObject::connect(this->m_gameLoop, &GameManager::TurnFinished, this->m_inputArea->GetHistoryDisplay(), &HistoryDisplay::RedrawHistory);

    QObject::connect(this->m_gameLoop, &GameManager::TurnFinished, this->m_gameVis, &GameVisualizer::UpdateViews);

    // Input
    QObject::connect(this->m_inputArea->GetPlayerInputControls(), &PlayerInput::InputConfirmed, this->m_gameLoop, &GameManager::InputConfirmationDetected);
    QObject::connect(this->m_gameVis, &GameVisualizer::InputDetected, this->m_gameLoop, &GameManager::InputConfirmationDetected);

    // Sound Connects
    QObject::connect(this->m_gameLoop, &GameManager::PlayInputAcceptSound, this, &GameView::PlayAcceptSound);
    QObject::connect(this->m_gameLoop, &GameManager::PlayInputErrorSound, this, &GameView::PlayErrorSound);
}

GameView::~GameView()
{
    delete(this->m_mainLayout);
}

void GameView::InitGame(GameData *data)
{
    *(this->m_data) = *data;     
    ShowGameInputView();
    this->m_gameVis->GameChanged();
    m_gameFinished = false;
    SaveGame();
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
    if(!m_gameFinished)
    {
        SaveGame();
    }
    else
    {
        WriteHighscoreToSave();
        ClearSave();
    }

    this->m_gameLoop->SuspendProcessingLoop();
    emit GameEnded(this->m_data);
}


void GameView::GameFinished()
{
    // Play WinSound

    m_gameFinished = true;

    QSound::play(":/sounds/Sounds/MUSIC EFFECT Solo Harp Positive 01 (stereo).wav");

    ShowWinner();
}

void GameView::ShowWinner()
{
    std::vector<Vector3> vec = GetAllFreePositions(this->m_data->GetField());

    if(vec.size() == 0)
    {

    }
    else
    {
        stringstream s;

        s << "The winner is : " << this->m_data->GetCurrentPlayer()->GetName().c_str() << "! YEAH!";

        this->WinLabel->setText(QString(s.str().c_str()));

        this->bottomViewLayout->setCurrentWidget(this->endView);

        Logger::GetLoggerIntance()->LogInfo(s.str());
    }

}

void GameView::PlayAcceptSound()
{
    QSound::play(":/sounds/Sounds/UI Beep Double Alternative (stereo).wav");
}

void GameView::PlayErrorSound()
{
    QSound::play(":/sounds/Sounds/UI Error Double Note Down (stereo).wav");
}

void GameView::ShowGameInputView()
{
    bottomViewLayout->setCurrentWidget(this->m_inputArea);
}


void GameView::SaveGame()
{
    ofstream saveFileOutput;
    saveFileOutput.open (SAVEFILENAME);

    stringstream s;

    s << GameData::Serialize(*this->m_data);

    saveFileOutput << s.str();

    saveFileOutput.close();
}

bool GameView::LoadGame()
{
    ifstream saveFile;
    saveFile.open (SAVEFILENAME);


    if(saveFile.is_open())
    {
        string s;
        getline (saveFile,s);
        saveFile.close();

        if(s.size() > 0)
        {



            Logger::GetLoggerIntance()->LogInfo("Before GameData Deserialization (GameView)", __FILE__, __LINE__);

            GameData *data = NULL;

            try
            {

                data = GameData::Deserialize(s);
                Logger::GetLoggerIntance()->LogInfo("After GameData Deserialization failed (GameView)", __FILE__, __LINE__);

                InitGame(data);
                return true;
            }
            catch(DeserializationException)
            {
                Logger::GetLoggerIntance()->LogInfo("GameData Deserialization FAILED (GameView)", __FILE__, __LINE__);
            }
        }
    }    

    return false;
}

void GameView::ClearSave()
{
    ofstream saveFileOutput;
    saveFileOutput.open (SAVEFILENAME);

    saveFileOutput.close();
}

void GameView::WriteHighscoreToSave()
{
    ifstream saveFile;
    saveFile.open (HIGHSCOREFILENAME);

    stringstream s;


    if(saveFile.is_open())
    {
        string oldString;
        getline (saveFile, oldString);
        saveFile.close();

        Logger::GetLoggerIntance()->LogInfo(oldString, __FILE__, __LINE__);

        if(oldString.size() > 0)
            s << oldString;
    }

    ofstream saveFileOutput;
    saveFileOutput.open (HIGHSCOREFILENAME);


    s << this->m_data->GetPlayer1()->GetName() << ";" << this->m_data->GetPlayer2()->GetName() << ";"
      << this->m_data->GetCurrentPlayer()->GetName() << ";" << this->m_data->GetHistory()->GetMoveCount() << "|";
    saveFileOutput << s.str();

    saveFileOutput.close();

}
