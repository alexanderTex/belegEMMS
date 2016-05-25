#include "./Gameview.h"

GameView::GameView(GameData *data, QWidget *parent) : QWidget(parent)
{
    QGridLayout *mainLayout = new QGridLayout(this);

    this->m_data = data;

    this->m_gameVis = new GameVisualizer(this->m_data, this);
    mainLayout->addWidget(this->m_gameVis);


    this->m_data->AddListener(this->GetVisualizer());

    this->m_inputArea = new GameInputArea(this->m_data, this);
    mainLayout->addWidget(this->m_inputArea);
}

GameView::~GameView()
{
    delete(this->m_gameVis);
    delete(this->m_inputArea);
}
