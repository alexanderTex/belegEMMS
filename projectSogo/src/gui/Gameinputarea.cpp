#include "GameInputArea.h"

GameInputArea::GameInputArea(GameData *data, QWidget *parent)
    :QWidget(parent)
{
    this->m_inputAreaLayout = new QStackedLayout(this);

    this->m_playerInput = new PlayerInput(data, this);
    this->m_inputAreaLayout->addWidget(this->m_playerInput);

    this->m_historyDisplay = new HistoryDisplay(this);
    this->m_inputAreaLayout->addWidget(this->m_historyDisplay);

}
