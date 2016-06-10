#include "GameInputArea.h"

GameInputArea::GameInputArea(GameManager *gameManager, QWidget *parent)
    :QWidget(parent)
{

    this->m_main = new QVBoxLayout(this);

    this->m_viewSelectionArea = new QWidget(this);
    this->m_main->addWidget(this->m_viewSelectionArea);

    this->m_selectionLayout = new QHBoxLayout(m_viewSelectionArea);

    this->m_historyView = new QPushButton("History", m_viewSelectionArea);
    QObject::connect(this->m_historyView, &QPushButton::clicked, this, &GameInputArea::SelectHistoryView);
    this->m_selectionLayout->addWidget(this->m_historyView);

    this->m_inputView = new QPushButton("Input", m_viewSelectionArea);
    QObject::connect(this->m_inputView, &QPushButton::clicked, this, &GameInputArea::SelectInputView);
    this->m_selectionLayout->addWidget(this->m_inputView);


    this->m_inputInfoDisplayArea = new QWidget(this);
    this->m_main->addWidget(this->m_inputInfoDisplayArea);

    this->m_inputAreaLayout = new QStackedLayout(this->m_inputInfoDisplayArea);

    this->m_playerInput = new PlayerInput(gameManager, m_inputInfoDisplayArea);
    this->m_inputAreaLayout->addWidget(this->m_playerInput);

    this->m_historyDisplay = new HistoryDisplay(gameManager->GetGameData(), m_inputInfoDisplayArea);
    this->m_inputAreaLayout->addWidget(this->m_historyDisplay);


}

GameInputArea::~GameInputArea()
{
    delete(m_main);
}

