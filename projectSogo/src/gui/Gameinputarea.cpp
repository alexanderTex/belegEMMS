#include "GameInputArea.h"

GameInputArea::GameInputArea(GameManager *gameManager, QWidget *parent)
    :QTabWidget(parent)
{
    this->m_playerInput = new PlayerInput(gameManager, this);
    this->addTab(this->m_playerInput, tr("Player Input"));
    this->m_historyDisplay = new HistoryDisplay(gameManager->GetGameData(), this);
    this->addTab(this->m_historyDisplay, tr("History Display"));
}

GameInputArea::~GameInputArea()
{
    delete(this->m_historyDisplay);
    delete(this->m_playerInput);
}

