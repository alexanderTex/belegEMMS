#include "./Gameview.h"

GameView::GameView(GameData *data, QWidget *parent)
    : QWidget(parent)
{
    m_mainLayout = new QGridLayout(this);

    this->m_data = data;

    this->m_gameVis = new GameVisualizer(this->m_data, this);
    m_mainLayout->addWidget(this->m_gameVis);


    this->m_data->AddListener(this->GetVisualizer());

    this->m_inputArea = new GameInputArea(this->m_data, this);
    m_mainLayout->addWidget(this->m_inputArea);
}

GameView::~GameView()
{
    delete(this->m_mainLayout);
    delete(this->m_gameVis);
    delete(this->m_inputArea);
}
